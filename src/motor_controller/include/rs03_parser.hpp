#pragma once
#include "motor_parser_base.hpp"

class RS03Parser : public MotorParserBase 
{
public:
    std::vector<uint8_t> packCommand(const motor_interfaces::msg::MotorCommand& cmd) override;
    motor_interfaces::msg::MotorStatus unpackStatus(const std::vector<uint8_t>& data) override;

    std::vector<uint8_t> enableMotor(uint8_t id) override;
    std::vector<uint8_t> disableMotor(uint8_t id) override;
    std::vector<uint8_t> setZero(uint8_t id) override;
    std::vector<uint8_t> setMode(uint8_t id, uint8_t mode) override;
};