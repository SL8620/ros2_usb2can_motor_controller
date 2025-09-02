// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motor_interfaces:msg/MotorStatus.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_INTERFACES__MSG__DETAIL__MOTOR_STATUS__BUILDER_HPP_
#define MOTOR_INTERFACES__MSG__DETAIL__MOTOR_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motor_interfaces/msg/detail/motor_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motor_interfaces
{

namespace msg
{

namespace builder
{

class Init_MotorStatus_current_torque
{
public:
  explicit Init_MotorStatus_current_torque(::motor_interfaces::msg::MotorStatus & msg)
  : msg_(msg)
  {}
  ::motor_interfaces::msg::MotorStatus current_torque(::motor_interfaces::msg::MotorStatus::_current_torque_type arg)
  {
    msg_.current_torque = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motor_interfaces::msg::MotorStatus msg_;
};

class Init_MotorStatus_current_velocity
{
public:
  explicit Init_MotorStatus_current_velocity(::motor_interfaces::msg::MotorStatus & msg)
  : msg_(msg)
  {}
  Init_MotorStatus_current_torque current_velocity(::motor_interfaces::msg::MotorStatus::_current_velocity_type arg)
  {
    msg_.current_velocity = std::move(arg);
    return Init_MotorStatus_current_torque(msg_);
  }

private:
  ::motor_interfaces::msg::MotorStatus msg_;
};

class Init_MotorStatus_current_position
{
public:
  explicit Init_MotorStatus_current_position(::motor_interfaces::msg::MotorStatus & msg)
  : msg_(msg)
  {}
  Init_MotorStatus_current_velocity current_position(::motor_interfaces::msg::MotorStatus::_current_position_type arg)
  {
    msg_.current_position = std::move(arg);
    return Init_MotorStatus_current_velocity(msg_);
  }

private:
  ::motor_interfaces::msg::MotorStatus msg_;
};

class Init_MotorStatus_id
{
public:
  explicit Init_MotorStatus_id(::motor_interfaces::msg::MotorStatus & msg)
  : msg_(msg)
  {}
  Init_MotorStatus_current_position id(::motor_interfaces::msg::MotorStatus::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_MotorStatus_current_position(msg_);
  }

private:
  ::motor_interfaces::msg::MotorStatus msg_;
};

class Init_MotorStatus_channel
{
public:
  explicit Init_MotorStatus_channel(::motor_interfaces::msg::MotorStatus & msg)
  : msg_(msg)
  {}
  Init_MotorStatus_id channel(::motor_interfaces::msg::MotorStatus::_channel_type arg)
  {
    msg_.channel = std::move(arg);
    return Init_MotorStatus_id(msg_);
  }

private:
  ::motor_interfaces::msg::MotorStatus msg_;
};

class Init_MotorStatus_device
{
public:
  Init_MotorStatus_device()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorStatus_channel device(::motor_interfaces::msg::MotorStatus::_device_type arg)
  {
    msg_.device = std::move(arg);
    return Init_MotorStatus_channel(msg_);
  }

private:
  ::motor_interfaces::msg::MotorStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motor_interfaces::msg::MotorStatus>()
{
  return motor_interfaces::msg::builder::Init_MotorStatus_device();
}

}  // namespace motor_interfaces

#endif  // MOTOR_INTERFACES__MSG__DETAIL__MOTOR_STATUS__BUILDER_HPP_
