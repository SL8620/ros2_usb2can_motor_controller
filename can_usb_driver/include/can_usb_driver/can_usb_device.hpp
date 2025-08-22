#pragma once

#include <thread>
#include <atomic>
#include <vector>
#include <string>
#include <mutex>
#include <string>
#include <functional>

#define CanPort_1      0x01
#define CanPort_2      0x02
#define CanId_classic  0x00
#define CanId_extended 0x01

namespace can_usb_driver{

    class CanUsbDevice;

    struct CanMessage 
    {
        uint8_t canPort;
        uint8_t canIdType;
        uint32_t id;
        std::vector<uint8_t> data;
    };

    using CanMessageCallback = std::function<void(const CanUsbDevice*,const CanMessage&)>;

    class CanUsbDevice 
    {
    public:
        std::string devName_;
        static std::mutex coutMutex_;
        
        CanUsbDevice(const std::string& devicePath = "", const std::string& devName_= "");
        ~CanUsbDevice();

        bool open();
        void close();

        bool sendCanMessage(const CanMessage& msg);
        void startReceiveThread();
        void stopReceiveThread();
        void setReceiveCallback(CanMessageCallback cb); 

        uint64_t getFramesSent() const { return framesSent_; }
        uint64_t getFramesReceived() const { return framesReceived_; }

    private:
        void receiveLoop();
        bool parseBuffer(std::vector<uint8_t>& buffer, CanMessage& msg);
        bool tryParseOneFrame(RingBuffer<16384>& rb, CanMessage& msg);

        std::string devicePath_;
        int fd_;
        std::thread recvThread_;
        std::atomic<bool> running_;
        std::mutex ioMutex_;
        CanMessageCallback receiveCallback_;

        std::atomic<uint64_t> framesSent_{0};       // 发送帧数量统计，调用公有方法可获取
        std::atomic<uint64_t> framesReceived_{0};   // 接收帧数量统计，调用公有方法可获取
    };
}

