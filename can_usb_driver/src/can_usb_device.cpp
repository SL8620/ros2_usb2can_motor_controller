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
#include "ringbuffer.hpp"       // 环形缓冲

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
                        : devicePath_(devicePath.empty() ? findDefaultDevice() : devicePath), devName_(deviceName), fd_(-1), running_(false) {}

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

    return true;
}

void CanUsbDevice::close() 
{
    if (fd_ >= 0) 
    {
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
    std::lock_guard<std::mutex> lock(ioMutex_);
    if (fd_ < 0) {
        RCLCPP_ERROR(rclcpp::get_logger("can_usb_device"), "CAN device not open!");
        return false;
    }

    uint8_t buf[16]; // 足够容纳一帧（头+flags+id+data）
    size_t idx = 0;

    buf[idx++] = 0xB0 | msg.canPort;
    buf[idx++] = ((msg.data.size() & 0x0F) << 4) | (msg.canIdType);

    if (msg.canIdType == CanId_extended) {
        buf[idx++] = (msg.id >> 24) & 0xFF;
        buf[idx++] = (msg.id >> 16) & 0xFF;
        buf[idx++] = (msg.id >>  8) & 0xFF;
        buf[idx++] =  msg.id        & 0xFF;
    } 
    else 
    {
        buf[idx++] = msg.id & 0xFF;
    }

    for (auto b : msg.data) 
    {
        if (idx >= sizeof(buf)) break; // 防止溢出
        buf[idx++] = b;
    }

    // 直接一次 write，返回是否写成功（全部字节写出）
    ssize_t n = ::write(fd_, buf, idx);
    framesSent_++;
    return n == (ssize_t)idx;
}


void CanUsbDevice::startReceiveThread() 
{
    running_ = true;
    recvThread_ = std::thread(&CanUsbDevice::receiveLoop, this);
}

void CanUsbDevice::stopReceiveThread() 
{
    running_ = false;
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

    while (running_) 
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
