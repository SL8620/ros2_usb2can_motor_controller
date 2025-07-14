// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motor_interfaces:msg/MotorControl.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_INTERFACES__MSG__DETAIL__MOTOR_CONTROL__TRAITS_HPP_
#define MOTOR_INTERFACES__MSG__DETAIL__MOTOR_CONTROL__TRAITS_HPP_

#include "motor_interfaces/msg/detail/motor_control__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<motor_interfaces::msg::MotorControl>()
{
  return "motor_interfaces::msg::MotorControl";
}

template<>
inline const char * name<motor_interfaces::msg::MotorControl>()
{
  return "motor_interfaces/msg/MotorControl";
}

template<>
struct has_fixed_size<motor_interfaces::msg::MotorControl>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<motor_interfaces::msg::MotorControl>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<motor_interfaces::msg::MotorControl>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOR_INTERFACES__MSG__DETAIL__MOTOR_CONTROL__TRAITS_HPP_
