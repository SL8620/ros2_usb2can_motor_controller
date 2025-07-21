// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motor_interfaces:msg/MotorStatus.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_INTERFACES__MSG__DETAIL__MOTOR_STATUS__STRUCT_H_
#define MOTOR_INTERFACES__MSG__DETAIL__MOTOR_STATUS__STRUCT_H_

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

/// Struct defined in msg/MotorStatus in the package motor_interfaces.
typedef struct motor_interfaces__msg__MotorStatus
{
  rosidl_runtime_c__String device;
  uint8_t channel;
  uint8_t id;
  float current_position;
  float current_velocity;
  float current_torque;
} motor_interfaces__msg__MotorStatus;

// Struct for a sequence of motor_interfaces__msg__MotorStatus.
typedef struct motor_interfaces__msg__MotorStatus__Sequence
{
  motor_interfaces__msg__MotorStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motor_interfaces__msg__MotorStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOR_INTERFACES__MSG__DETAIL__MOTOR_STATUS__STRUCT_H_
