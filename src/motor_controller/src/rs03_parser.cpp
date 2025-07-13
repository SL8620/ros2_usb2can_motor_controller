/*** 
 * @Author: SL8620
 * @Date: 2025-07-12 15:43:37
 * @LastEditTime: 2025-07-13 19:35:30
 * @LastEditors: SL8620
 * @Description: 
 * @FilePath: \motor_controller\src\motor_controller\src\rs03_parser.cpp
 * @
 */
#include "motor_controller/rs03_parser.hpp"
#include "motor_controller/math_ops.hpp"

#define P_MIN      -12.57f
#define P_MAX       12.57f
#define V_MIN      -20.0f
#define V_MAX       20.0f
#define KP_MIN      0.0f
#define KP_MAX      5000.0f
#define KD_MIN      0.0f
#define KD_MAX      100.0f
#define T_MIN      -60.0f
#define T_MAX       60.0f

RS03Parser::RS03Parser(std::shared_ptr<can_usb_driver::CanUsbDevice> device,uint8_t channel,uint8_t id)
{
    device_ = device;
    channel_ = channel;
    id_ = id;
}

void RS03Parser::enable_motor()
{
    can_usb_driver::CanMessage msg;
    msg.channel = channel_;
    msg.id = id_;
    msg.data = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC};

    device_->send(msg);
}

void RS03Parser::disable_motor()
{
    can_usb_driver::CanMessage msg;
    msg.channel = channel_;
    msg.id = id_;
    msg.data = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD};

    device_->send(msg);
}

void RS03Parser::zero_position()
{
    can_usb_driver::CanMessage msg;
    msg.channel = channel_;
    msg.id = id_;
    msg.data = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE};

    device_->send(msg);
}

void RS03Parser::set_mode(uint8_t mode)
{
    // mode 范围在 0~5（举例），转换为协议格式：
    can_usb_driver::CanMessage msg;
    msg.channel = channel_;
    msg.id = id_;
    msg.data = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, static_cast<uint8_t>(mode)};

    device_->send(msg);
}

void RS03Parser::packCommand(const motor_interfaces::msg::MotorControl& ctrl, std::vector<uint8_t>& data)
{
    float p_des = fminf(fmaxf(P_MIN, ctrl.position), P_MAX);                    
    float v_des = fminf(fmaxf(V_MIN, ctrl.velocity), V_MAX);
    float t_des = fminf(fmaxf(T_MIN, ctrl.torque  ), T_MAX);
    float kp    = fminf(fmaxf(KP_MIN, ctrl.kp      ), KP_MAX);
    float kd    = fminf(fmaxf(KD_MIN, ctrl.kd      ), KD_MAX);

    uint16_t  p_int = float_to_uint(p_des, P_MIN, P_MAX, 16);            
    uint16_t  v_int = float_to_uint(v_des, V_MIN, V_MAX, 12);
    uint16_t  t_int = float_to_uint(t_des, T_MIN, T_MAX, 12);
    uint16_t kp_int = float_to_uint(kp,    KP_MIN, KP_MAX, 12);
    uint16_t kd_int = float_to_uint(kd,    KD_MIN, KD_MAX, 12);

    data.resize(8);
    data[0] = (p_int >> 8) & 0xFF;      
    data[1] =  p_int & 0xFF;
    data[2] = (v_int >> 4) & 0xFF;
    data[3] = ((v_int & 0x0F) << 4) | ((kp_int >> 8) & 0x0F);
    data[4] = kp_int & 0xFF;
    data[5] = (kd_int >> 4) & 0xFF;
    data[6] = ((kd_int & 0x0F) << 4) | ((t_int >> 8) & 0x0F);
    data[7] = t_int & 0xFF;
}


void RS03Parser::unpackStatus(const std::vector<uint8_t>& data, motor_interfaces::msg::MotorStatus& status)
{
    uint16_t p_int = (msg.data[1]<<8)|msg.data[2];
    uint16_t v_int = (msg.data[3]<<4)|(msg.data[4]>>4);
    uint16_t i_int = ((msg.data[4]&0x0F)<<8)|msg.data[5];

    float position = uint_to_float(p_int, P_MIN, P_MAX, 16);
    float velocity = uint_to_float(v_int, V_MIN, V_MAX, 12);
    float torque   = uint_to_float(i_int, -T_MAX, T_MAX, 12);

    status.current_position = position;
    status.current_velocity = velocity;
    status.current_torque   = torque;
}
