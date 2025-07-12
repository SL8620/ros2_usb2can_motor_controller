#include "motor_controller/rs03_parser.hpp"

std::vector<uint8_t> RS03Parser::packCommand(const motor_interfaces::msg::MotorCommand& cmd) {
    std::vector<uint8_t> data(8);
    // 示例打包协议
    data[0] = cmd.id;
    // 假设position编码成两个字节
    int pos = static_cast<int>(cmd.position * 1000);
    data[1] = (pos >> 8) & 0xFF;
    data[2] = pos & 0xFF;
    return data;
}

motor_interfaces::msg::MotorStatus RS03Parser::unpackStatus(const std::vector<uint8_t>& data) {
    motor_interfaces::msg::MotorStatus status;
    status.id = data[0];
    int pos = (data[1] << 8) | data[2];
    status.current_position = pos / 1000.0;
    return status;
}

// 扩展指令
std::vector<uint8_t> RS03Parser::enableMotor(uint8_t id) {
    return { id, 0x01 };
}
std::vector<uint8_t> RS03Parser::disableMotor(uint8_t id) {
    return { id, 0x02 };
}
std::vector<uint8_t> RS03Parser::setZero(uint8_t id) {
    return { id, 0x03 };
}
std::vector<uint8_t> RS03Parser::setMode(uint8_t id, uint8_t mode) {
    return { id, 0x04, mode };
}