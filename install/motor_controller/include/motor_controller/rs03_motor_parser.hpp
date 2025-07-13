#pragma once

#include "motor_controller/motor_parser_base.hpp"
#include "can_usb_driver/can_usb_device.hpp"

class RS03Parser : public MotorParserBase
{
public:
    RS03Parser(std::shared_ptr<can_usb_driver::CanUsbDevice> device,
               uint8_t channel,
               uint8_t id);

    void packCommand(const motor_interfaces::msg::MotorControl& cmd,
                     std::vector<uint8_t>& data) override;

    void unpackStatus(const std::vector<uint8_t>& data,
                      motor_interfaces::msg::MotorStatus& status) override;

    void enable_motor() override;
    void disable_motor() override;
    void zero_position() override;
    void set_mode(uint8_t mode) override;
};
