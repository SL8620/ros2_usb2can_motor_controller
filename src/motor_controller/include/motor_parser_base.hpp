/*** 
 * @Author: SL8620
 * @Date: 2025-07-12 15:43:37
 * @LastEditTime: 2025-07-13 19:48:24
 * @LastEditors: SL8620
 * @Description: 
 * @FilePath: \motor_controller\src\motor_controller\include\motor_parser_base.hpp
 * @
 */
#pragma once
#include <vector>
#include <string>
#include "can_usb_driver/can_usb_device.hpp"
#include "motor_interfaces/msg/motor_command.hpp"
#include "motor_interfaces/msg/motor_control.hpp"
#include "motor_interfaces/msg/motor_status.hpp"

class MotorParserBase
{
public:
    virtual ~MotorParserBase() = default;

    virtual void packCommand(const std::shared_ptr<const motor_interfaces::msg::MotorControl>& cmd, std::vector<uint8_t>& data) = 0;

    virtual void unpackStatus(const std::vector<uint8_t>& data, motor_interfaces::msg::MotorStatus& status) = 0;

    virtual void enable_motor() = 0;
    virtual void disable_motor() = 0;
    virtual void zero_position() = 0;
    virtual void set_mode(uint8_t mode) = 0;

protected:
    // 添加这些接口用于派生类访问 CAN
    std::shared_ptr<can_usb_driver::CanUsbDevice> device_;
    uint8_t channel_;
    uint8_t id_;
};
