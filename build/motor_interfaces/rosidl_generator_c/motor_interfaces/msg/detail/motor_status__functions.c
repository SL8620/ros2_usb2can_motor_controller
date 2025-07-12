// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motor_interfaces:msg/MotorStatus.idl
// generated code does not contain a copyright notice
#include "motor_interfaces/msg/detail/motor_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
motor_interfaces__msg__MotorStatus__init(motor_interfaces__msg__MotorStatus * msg)
{
  if (!msg) {
    return false;
  }
  // device
  // channel
  // id
  // current_position
  // current_velocity
  // current_torque
  return true;
}

void
motor_interfaces__msg__MotorStatus__fini(motor_interfaces__msg__MotorStatus * msg)
{
  if (!msg) {
    return;
  }
  // device
  // channel
  // id
  // current_position
  // current_velocity
  // current_torque
}

bool
motor_interfaces__msg__MotorStatus__are_equal(const motor_interfaces__msg__MotorStatus * lhs, const motor_interfaces__msg__MotorStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // device
  if (lhs->device != rhs->device) {
    return false;
  }
  // channel
  if (lhs->channel != rhs->channel) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // current_position
  if (lhs->current_position != rhs->current_position) {
    return false;
  }
  // current_velocity
  if (lhs->current_velocity != rhs->current_velocity) {
    return false;
  }
  // current_torque
  if (lhs->current_torque != rhs->current_torque) {
    return false;
  }
  return true;
}

bool
motor_interfaces__msg__MotorStatus__copy(
  const motor_interfaces__msg__MotorStatus * input,
  motor_interfaces__msg__MotorStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // device
  output->device = input->device;
  // channel
  output->channel = input->channel;
  // id
  output->id = input->id;
  // current_position
  output->current_position = input->current_position;
  // current_velocity
  output->current_velocity = input->current_velocity;
  // current_torque
  output->current_torque = input->current_torque;
  return true;
}

motor_interfaces__msg__MotorStatus *
motor_interfaces__msg__MotorStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_interfaces__msg__MotorStatus * msg = (motor_interfaces__msg__MotorStatus *)allocator.allocate(sizeof(motor_interfaces__msg__MotorStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motor_interfaces__msg__MotorStatus));
  bool success = motor_interfaces__msg__MotorStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motor_interfaces__msg__MotorStatus__destroy(motor_interfaces__msg__MotorStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motor_interfaces__msg__MotorStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motor_interfaces__msg__MotorStatus__Sequence__init(motor_interfaces__msg__MotorStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_interfaces__msg__MotorStatus * data = NULL;

  if (size) {
    data = (motor_interfaces__msg__MotorStatus *)allocator.zero_allocate(size, sizeof(motor_interfaces__msg__MotorStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motor_interfaces__msg__MotorStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motor_interfaces__msg__MotorStatus__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
motor_interfaces__msg__MotorStatus__Sequence__fini(motor_interfaces__msg__MotorStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      motor_interfaces__msg__MotorStatus__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

motor_interfaces__msg__MotorStatus__Sequence *
motor_interfaces__msg__MotorStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_interfaces__msg__MotorStatus__Sequence * array = (motor_interfaces__msg__MotorStatus__Sequence *)allocator.allocate(sizeof(motor_interfaces__msg__MotorStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motor_interfaces__msg__MotorStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motor_interfaces__msg__MotorStatus__Sequence__destroy(motor_interfaces__msg__MotorStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motor_interfaces__msg__MotorStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motor_interfaces__msg__MotorStatus__Sequence__are_equal(const motor_interfaces__msg__MotorStatus__Sequence * lhs, const motor_interfaces__msg__MotorStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motor_interfaces__msg__MotorStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motor_interfaces__msg__MotorStatus__Sequence__copy(
  const motor_interfaces__msg__MotorStatus__Sequence * input,
  motor_interfaces__msg__MotorStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motor_interfaces__msg__MotorStatus);
    motor_interfaces__msg__MotorStatus * data =
      (motor_interfaces__msg__MotorStatus *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motor_interfaces__msg__MotorStatus__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          motor_interfaces__msg__MotorStatus__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motor_interfaces__msg__MotorStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
