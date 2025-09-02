// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motor_interfaces:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_INTERFACES__MSG__DETAIL__MOTOR_COMMAND__STRUCT_H_
#define MOTOR_INTERFACES__MSG__DETAIL__MOTOR_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'device'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/MotorCommand in the package motor_interfaces.
typedef struct motor_interfaces__msg__MotorCommand
{
  rosidl_runtime_c__String device;
  uint8_t channel;
  uint8_t id;
  /// 0: enable, 1: disable, 2: zeroing, 3: set mode ...
  uint8_t command_type;
  /// 仅当 command_type = 3 时使用，0: position, 1: velocity 等
  uint8_t mode_type;
} motor_interfaces__msg__MotorCommand;

// Struct for a sequence of motor_interfaces__msg__MotorCommand.
typedef struct motor_interfaces__msg__MotorCommand__Sequence
{
  motor_interfaces__msg__MotorCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motor_interfaces__msg__MotorCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOR_INTERFACES__MSG__DETAIL__MOTOR_COMMAND__STRUCT_H_
