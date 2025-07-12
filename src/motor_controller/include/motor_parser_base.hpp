#pragma once
#include <vector>
#include <string>
#include "can_usb_driver/can_usb_device.hpp"
#include "motor_interfaces/msg/motor_command.hpp"
#include "motor_interfaces/msg/motor_status.hpp"

class MotorParserBase {
public:
    virtual ~MotorParserBase() = default;

    virtual std::vector<uint8_t> packCommand(const motor_interfaces::msg::MotorCommand& cmd) = 0;
    virtual motor_interfaces::msg::MotorStatus unpackStatus(const std::vector<uint8_t>& data) = 0;

    // 可选扩展功能
    virtual std::vector<uint8_t> enableMotor(uint8_t id) = 0;
    virtual std::vector<uint8_t> disableMotor(uint8_t id) = 0;
    virtual std::vector<uint8_t> setZero(uint8_t id) = 0;
    virtual std::vector<uint8_t> setMode(uint8_t id, uint8_t mode) = 0;
};