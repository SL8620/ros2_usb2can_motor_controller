// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motor_interfaces:msg/MotorStatus.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_INTERFACES__MSG__DETAIL__MOTOR_STATUS__TRAITS_HPP_
#define MOTOR_INTERFACES__MSG__DETAIL__MOTOR_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "motor_interfaces/msg/detail/motor_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace motor_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const MotorStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: device
  {
    out << "device: ";
    rosidl_generator_traits::value_to_yaml(msg.device, out);
    out << ", ";
  }

  // member: channel
  {
    out << "channel: ";
    rosidl_generator_traits::value_to_yaml(msg.channel, out);
    out << ", ";
  }

  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: current_position
  {
    out << "current_position: ";
    rosidl_generator_traits::value_to_yaml(msg.current_position, out);
    out << ", ";
  }

  // member: current_velocity
  {
    out << "current_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.current_velocity, out);
    out << ", ";
  }

  // member: current_torque
  {
    out << "current_torque: ";
    rosidl_generator_traits::value_to_yaml(msg.current_torque, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MotorStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: device
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "device: ";
    rosidl_generator_traits::value_to_yaml(msg.device, out);
    out << "\n";
  }

  // member: channel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "channel: ";
    rosidl_generator_traits::value_to_yaml(msg.channel, out);
    out << "\n";
  }

  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: current_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_position: ";
    rosidl_generator_traits::value_to_yaml(msg.current_position, out);
    out << "\n";
  }

  // member: current_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.current_velocity, out);
    out << "\n";
  }

  // member: current_torque
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_torque: ";
    rosidl_generator_traits::value_to_yaml(msg.current_torque, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MotorStatus & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace motor_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use motor_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const motor_interfaces::msg::MotorStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  motor_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motor_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const motor_interfaces::msg::MotorStatus & msg)
{
  return motor_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<motor_interfaces::msg::MotorStatus>()
{
  return "motor_interfaces::msg::MotorStatus";
}

template<>
inline const char * name<motor_interfaces::msg::MotorStatus>()
{
  return "motor_interfaces/msg/MotorStatus";
}

template<>
struct has_fixed_size<motor_interfaces::msg::MotorStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<motor_interfaces::msg::MotorStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<motor_interfaces::msg::MotorStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOR_INTERFACES__MSG__DETAIL__MOTOR_STATUS__TRAITS_HPP_
