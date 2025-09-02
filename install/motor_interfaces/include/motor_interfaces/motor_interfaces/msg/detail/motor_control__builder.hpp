// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motor_interfaces:msg/MotorControl.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_INTERFACES__MSG__DETAIL__MOTOR_CONTROL__BUILDER_HPP_
#define MOTOR_INTERFACES__MSG__DETAIL__MOTOR_CONTROL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motor_interfaces/msg/detail/motor_control__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motor_interfaces
{

namespace msg
{

namespace builder
{

class Init_MotorControl_kd
{
public:
  explicit Init_MotorControl_kd(::motor_interfaces::msg::MotorControl & msg)
  : msg_(msg)
  {}
  ::motor_interfaces::msg::MotorControl kd(::motor_interfaces::msg::MotorControl::_kd_type arg)
  {
    msg_.kd = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motor_interfaces::msg::MotorControl msg_;
};

class Init_MotorControl_kp
{
public:
  explicit Init_MotorControl_kp(::motor_interfaces::msg::MotorControl & msg)
  : msg_(msg)
  {}
  Init_MotorControl_kd kp(::motor_interfaces::msg::MotorControl::_kp_type arg)
  {
    msg_.kp = std::move(arg);
    return Init_MotorControl_kd(msg_);
  }

private:
  ::motor_interfaces::msg::MotorControl msg_;
};

class Init_MotorControl_torque
{
public:
  explicit Init_MotorControl_torque(::motor_interfaces::msg::MotorControl & msg)
  : msg_(msg)
  {}
  Init_MotorControl_kp torque(::motor_interfaces::msg::MotorControl::_torque_type arg)
  {
    msg_.torque = std::move(arg);
    return Init_MotorControl_kp(msg_);
  }

private:
  ::motor_interfaces::msg::MotorControl msg_;
};

class Init_MotorControl_velocity
{
public:
  explicit Init_MotorControl_velocity(::motor_interfaces::msg::MotorControl & msg)
  : msg_(msg)
  {}
  Init_MotorControl_torque velocity(::motor_interfaces::msg::MotorControl::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_MotorControl_torque(msg_);
  }

private:
  ::motor_interfaces::msg::MotorControl msg_;
};

class Init_MotorControl_position
{
public:
  explicit Init_MotorControl_position(::motor_interfaces::msg::MotorControl & msg)
  : msg_(msg)
  {}
  Init_MotorControl_velocity position(::motor_interfaces::msg::MotorControl::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_MotorControl_velocity(msg_);
  }

private:
  ::motor_interfaces::msg::MotorControl msg_;
};

class Init_MotorControl_id
{
public:
  explicit Init_MotorControl_id(::motor_interfaces::msg::MotorControl & msg)
  : msg_(msg)
  {}
  Init_MotorControl_position id(::motor_interfaces::msg::MotorControl::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_MotorControl_position(msg_);
  }

private:
  ::motor_interfaces::msg::MotorControl msg_;
};

class Init_MotorControl_channel
{
public:
  explicit Init_MotorControl_channel(::motor_interfaces::msg::MotorControl & msg)
  : msg_(msg)
  {}
  Init_MotorControl_id channel(::motor_interfaces::msg::MotorControl::_channel_type arg)
  {
    msg_.channel = std::move(arg);
    return Init_MotorControl_id(msg_);
  }

private:
  ::motor_interfaces::msg::MotorControl msg_;
};

class Init_MotorControl_device
{
public:
  Init_MotorControl_device()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorControl_channel device(::motor_interfaces::msg::MotorControl::_device_type arg)
  {
    msg_.device = std::move(arg);
    return Init_MotorControl_channel(msg_);
  }

private:
  ::motor_interfaces::msg::MotorControl msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motor_interfaces::msg::MotorControl>()
{
  return motor_interfaces::msg::builder::Init_MotorControl_device();
}

}  // namespace motor_interfaces

#endif  // MOTOR_INTERFACES__MSG__DETAIL__MOTOR_CONTROL__BUILDER_HPP_
