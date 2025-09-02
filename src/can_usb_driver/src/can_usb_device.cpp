#include "can_usb_driver/can_usb_device.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <dirent.h>
#include <cstring>
#include <chrono>
#include <thread>
#include <algorithm>

#include "rclcpp/rclcpp.hpp"    // ROS 2核心功能

using namespace can_usb_driver;

std::mutex CanUsbDevice::coutMutex_;

static std::string findDefaultDevice() 
{
    DIR* dir = opendir("/dev");
    if (!dir) return "";
    struct dirent* ent;
    while ((ent = readdir(dir)) != nullptr) 
    {
        if (strncmp(ent->d_name, "ttyACM", 6) == 0) 
        {
            closedir(dir);
            return "/dev/" + std::string(ent->d_name);
        }
    }
    closedir(dir);
    return "";
}

CanUsbDevice::CanUsbDevice(const std::string& devicePath, const std::string& deviceName) 
                        : devicePath_(devicePath.empty() ? findDefaultDevice() : devicePath), devName_(deviceName), fd_(-1), runningRx_(false) {}

CanUsbDevice::~CanUsbDevice() 
{
    stopReceiveThread();
    close();
}

bool CanUsbDevice::open() 
{
    fd_ = ::open(devicePath_.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd_ < 0) 
    {
        RCLCPP_ERROR(rclcpp::get_logger("can_usb_device"), "Failed to open %s: %s", devicePath_.c_str(), strerror(errno));
        return false;
    } 
    else 
    {
        RCLCPP_INFO(rclcpp::get_logger("can_usb_device"), "Successfully opened %s (fd=%d)", devicePath_.c_str(), fd_);
    }

    termios tty{};
    if (tcgetattr(fd_, &tty) != 0) 
    {
        RCLCPP_INFO(rclcpp::get_logger("can_usb_device"), "Failed to get termios\n");
        // std::cerr << "Failed to get termios\n";
        return false;
    }

    // 串口设置
    tty.c_iflag = 0;                             // 输入模式
    tty.c_oflag = 0;                             // 输出模式
    tty.c_cflag = CREAD | CLOCAL | CS8;          // 控制模式：8位、无校验、启用接收、本地连接
    tty.c_cflag &= ~CRTSCTS;                     // 关闭硬件流控
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);      // 禁用软件流控
    tty.c_lflag = 0;                             // 非规范模式

    cfsetospeed(&tty, B921600);                  // 输出波特率
    cfsetispeed(&tty, B921600);                  // 输入波特率

    tty.c_cc[VMIN] = 0;                          // 非阻塞读取
    tty.c_cc[VTIME] = 1;                         // 超时时间 100ms

    if (tcsetattr(fd_, TCSANOW, &tty) != 0) 
    {
        std::cerr << "Failed to set termios\n";
        return false;
    }

    runningTx_ = true;   // ⚠ 在创建线程前设置
    tx_thread_ = std::thread(&CanUsbDevice::txThreadFunc, this, 300);

    return true;
}

void CanUsbDevice::close() 
{
    runningTx_ = false;
    tx_cv_.notify_all();
    if (tx_thread_.joinable()) tx_thread_.join();

    runningRx_ = false;
    if (recvThread_.joinable()) recvThread_.join();

    if (fd_ >= 0) {
        ::close(fd_);
        fd_ = -1;
    }
}

void CanUsbDevice::setReceiveCallback(CanMessageCallback cb)
{
    receiveCallback_ = std::move(cb);
}

bool CanUsbDevice::sendCanMessage(const CanMessage& msg) 
{
    int port = msg.canPort;
    if (port != CanPort_1 && port != CanPort_2) return false;

    {
        std::lock_guard<std::mutex> lock(tx_queues_[port].mtx);
        tx_queues_[port].queue.push_back(msg);
    }
    
    return true;
}

void CanUsbDevice::txThreadFunc(int interval_us=300) 
{
    auto logger = rclcpp::get_logger("can_usb_device_tx");
    
    while (runningTx_) 
    {
        for (int port = CanPort_1; port <= CanPort_2; ++port) 
        {
            std::vector<CanMessage> msgs_to_send;
            {
                std::lock_guard<std::mutex> lock(tx_queues_[port].mtx);
                msgs_to_send.swap(tx_queues_[port].queue);
            }

            if (!msgs_to_send.empty()) 
            {
                for (const auto& msg : msgs_to_send) 
                {
                    // 打印调试信息
                    std::stringstream ss;
                    ss << "准备发送 CAN 消息 - 端口: " << static_cast<int>(msg.canPort)
                       << " ID: 0x" << std::hex << std::setw(8) << std::setfill('0') << msg.id
                       << " 类型: " << (msg.canIdType == CanId_extended ? "扩展帧" : "标准帧")
                       << " 长度: " << std::dec << msg.data.size()
                       << " 数据: ";
                    
                    for (uint8_t byte : msg.data) {
                        ss << std::hex << std::setw(2) << std::setfill('0') 
                           << static_cast<int>(byte) << " ";
                    }
                    // RCLCPP_DEBUG(logger, "%s", ss.str().c_str());

                    // 按照 sendCanMessage 的格式打包报文
                    std::vector<uint8_t> buf;
                    buf.push_back(0xB0 | msg.canPort);
                    buf.push_back(((msg.data.size() & 0x0F) << 4) | (msg.canIdType));

                    if (msg.canIdType == CanId_extended) 
                    {
                        buf.push_back((msg.id >> 24) & 0xFF);
                        buf.push_back((msg.id >> 16) & 0xFF);
                        buf.push_back((msg.id >>  8) & 0xFF);
                        buf.push_back( msg.id        & 0xFF);
                    } 
                    else 
                    {
                        buf.push_back(msg.id & 0xFF);
                    }

                    buf.insert(buf.end(), msg.data.begin(), msg.data.end());

                    // 打印实际发送的原始数据
                    std::stringstream raw_ss;
                    raw_ss << "实际发送数据 (" << buf.size() << " 字节): ";
                    for (size_t i = 0; i < buf.size(); ++i) {
                        raw_ss << std::hex << std::setw(2) << std::setfill('0') 
                              << static_cast<int>(buf[i]) << " ";
                        if ((i + 1) % 8 == 0) raw_ss << "\n                      ";
                    }
                    // RCLCPP_DEBUG(logger, "%s", raw_ss.str().c_str());

                    // 发送数据
                    ssize_t bytes_written = write(fd_, buf.data(), buf.size());
                    if (bytes_written != static_cast<ssize_t>(buf.size())) {
                        // RCLCPP_ERROR(logger, "发送失败，预期 %zu 字节，实际 %zd 字节", 
                        //             buf.size(), bytes_written);
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::microseconds(interval_us));
    }
}


void CanUsbDevice::startReceiveThread() 
{
    runningRx_ = true;
    recvThread_ = std::thread(&CanUsbDevice::receiveLoop, this);
}

void CanUsbDevice::stopReceiveThread() 
{
    runningRx_ = false;
    if (recvThread_.joinable()) 
    {
        recvThread_.join();
    }
}

void CanUsbDevice::receiveLoop() 
{
    RingBuffer<16384> rb;         // 16KB 缓冲，够 0.5s CAN burst
    uint8_t temp[512];            // 单次批量读
    auto logger = rclcpp::get_logger("can_usb_device");

    while (runningRx_) 
    {
        ssize_t n = ::read(fd_, temp, sizeof(temp));
        if (n > 0) 
        {
            rb.push(temp, static_cast<size_t>(n));

            CanMessage msg;
            while (tryParseOneFrame(rb, msg)) 
            {
                if (receiveCallback_) 
                {
                    receiveCallback_(this, msg);
                    framesReceived_++;
                }
            }
        } 
        else if (n < 0) 
        {
            if (errno == EAGAIN || errno == EINTR) 
            {
                continue; // 临时错误
            }
            RCLCPP_ERROR(logger, "Read error: %s", strerror(errno));
            break; // 设备断开或致命错误
        }
        // n == 0 表示超时，不是错误，继续
    }
}

bool CanUsbDevice::parseBuffer(std::vector<uint8_t>& buffer, CanMessage& msg) 
{
    if (buffer.size() < 4) return false;

    auto it = std::find(buffer.begin(), buffer.end(), 0xA5);
    if (it == buffer.end()) 
    {
        buffer.clear();
        return false;
    }

    if (std::distance(it, buffer.end()) < 4) return false;

    size_t start = std::distance(buffer.begin(), it);
    uint8_t ctrl = buffer[start + 1];       // 0xB1 / 0xB2
    uint8_t flags = buffer[start + 2];      // dlc | idType
    bool isExt = (flags & 0x10);
    uint8_t dlc = flags & 0x0F;

    size_t idLen = isExt ? 4 : 1;
    size_t totalLen = 1 + 1 + 1 + idLen + dlc + 1;

    if (start + totalLen > buffer.size()) 
    {
        return false;
    }

    if (buffer[start + totalLen - 1] != 0x5A) 
    {
        buffer.erase(buffer.begin(), buffer.begin() + start + 1);
        return false;
    }

    msg.canPort = ctrl & 0x0F;
    msg.canIdType = isExt ?  CanId_extended : CanId_classic;
    msg.id = 0;
    if (msg.canIdType == CanId_extended) 
    {
        msg.id = (buffer[start + 3] << 24) | (buffer[start + 4] << 16)| (buffer[start + 5] << 8) | buffer[start + 6];
    } 
    else 
    {
        msg.id = buffer[start + 3];
    }

    size_t dataStart = start + 3 + idLen;
    msg.data.assign(buffer.begin() + dataStart, buffer.begin() + dataStart + dlc);

    buffer.erase(buffer.begin(), buffer.begin() + start + totalLen);
    return true;
}

// 使用环形缓冲解包
bool CanUsbDevice::tryParseOneFrame(RingBuffer<16384>& rb, CanMessage& msg) 
{
    if (rb.size() < 4) return false;

    auto it = rb.findFirst(0xA5);
    if (!it) {
        rb.pop(rb.size()); // 没找到帧头，丢弃全部
        return false;
    }

    size_t start = *it;
    if (rb.size() - start < 4) return false;

    uint8_t ctrl  = rb.get(start + 1);
    uint8_t flags = rb.get(start + 2);
    bool isExt    = (flags & 0x10);
    uint8_t dlc   = flags & 0x0F;

    size_t idLen   = isExt ? 4 : 1;
    size_t totalLen = 1 + 1 + 1 + idLen + dlc + 1; // A5+ctrl+flags+id+data+5A

    if (rb.size() - start < totalLen) return false;

    if (rb.get(start + totalLen - 1) != 0x5A) {
        rb.pop(start + 1); // 错帧，丢掉到下一个候选起点
        return false;
    }

    msg.canPort   = ctrl & 0x0F;
    msg.canIdType = isExt ? CanId_extended : CanId_classic;
    msg.id = 0;

    if (isExt) {
        msg.id = (rb.get(start + 3) << 24) |
                 (rb.get(start + 4) << 16) |
                 (rb.get(start + 5) << 8)  |
                  rb.get(start + 6);
    } else {
        msg.id = rb.get(start + 3);
    }

    size_t dataStart = start + 3 + idLen;
    msg.data.clear();
    msg.data.reserve(dlc);
    for (size_t i = 0; i < dlc; ++i) {
        msg.data.push_back(rb.get(dataStart + i));
    }

    rb.pop(start + totalLen); // 消费掉整帧
    return true;
}
