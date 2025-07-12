// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motor_interfaces:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_INTERFACES__MSG__DETAIL__MOTOR_COMMAND__BUILDER_HPP_
#define MOTOR_INTERFACES__MSG__DETAIL__MOTOR_COMMAND__BUILDER_HPP_

#include "motor_interfaces/msg/detail/motor_command__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace motor_interfaces
{

namespace msg
{

namespace builder
{

class Init_MotorCommand_time_ms
{
public:
  explicit Init_MotorCommand_time_ms(::motor_interfaces::msg::MotorCommand & msg)
  : msg_(msg)
  {}
  ::motor_interfaces::msg::MotorCommand time_ms(::motor_interfaces::msg::MotorCommand::_time_ms_type arg)
  {
    msg_.time_ms = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motor_interfaces::msg::MotorCommand msg_;
};

class Init_MotorCommand_velocity
{
public:
  explicit Init_MotorCommand_velocity(::motor_interfaces::msg::MotorCommand & msg)
  : msg_(msg)
  {}
  Init_MotorCommand_time_ms velocity(::motor_interfaces::msg::MotorCommand::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_MotorCommand_time_ms(msg_);
  }

private:
  ::motor_interfaces::msg::MotorCommand msg_;
};

class Init_MotorCommand_position
{
public:
  explicit Init_MotorCommand_position(::motor_interfaces::msg::MotorCommand & msg)
  : msg_(msg)
  {}
  Init_MotorCommand_velocity position(::motor_interfaces::msg::MotorCommand::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_MotorCommand_velocity(msg_);
  }

private:
  ::motor_interfaces::msg::MotorCommand msg_;
};

class Init_MotorCommand_id
{
public:
  explicit Init_MotorCommand_id(::motor_interfaces::msg::MotorCommand & msg)
  : msg_(msg)
  {}
  Init_MotorCommand_position id(::motor_interfaces::msg::MotorCommand::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_MotorCommand_position(msg_);
  }

private:
  ::motor_interfaces::msg::MotorCommand msg_;
};

class Init_MotorCommand_channel
{
public:
  explicit Init_MotorCommand_channel(::motor_interfaces::msg::MotorCommand & msg)
  : msg_(msg)
  {}
  Init_MotorCommand_id channel(::motor_interfaces::msg::MotorCommand::_channel_type arg)
  {
    msg_.channel = std::move(arg);
    return Init_MotorCommand_id(msg_);
  }

private:
  ::motor_interfaces::msg::MotorCommand msg_;
};

class Init_MotorCommand_device
{
public:
  Init_MotorCommand_device()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorCommand_channel device(::motor_interfaces::msg::MotorCommand::_device_type arg)
  {
    msg_.device = std::move(arg);
    return Init_MotorCommand_channel(msg_);
  }

private:
  ::motor_interfaces::msg::MotorCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motor_interfaces::msg::MotorCommand>()
{
  return motor_interfaces::msg::builder::Init_MotorCommand_device();
}

}  // namespace motor_interfaces

#endif  // MOTOR_INTERFACES__MSG__DETAIL__MOTOR_COMMAND__BUILDER_HPP_
