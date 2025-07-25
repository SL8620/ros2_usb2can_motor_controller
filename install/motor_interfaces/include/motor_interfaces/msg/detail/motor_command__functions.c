// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motor_interfaces:msg/MotorCommand.idl
// generated code does not contain a copyright notice
#include "motor_interfaces/msg/detail/motor_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `device`
#include "rosidl_runtime_c/string_functions.h"

bool
motor_interfaces__msg__MotorCommand__init(motor_interfaces__msg__MotorCommand * msg)
{
  if (!msg) {
    return false;
  }
  // device
  if (!rosidl_runtime_c__String__init(&msg->device)) {
    motor_interfaces__msg__MotorCommand__fini(msg);
    return false;
  }
  // channel
  // id
  // command_type
  // mode_type
  return true;
}

void
motor_interfaces__msg__MotorCommand__fini(motor_interfaces__msg__MotorCommand * msg)
{
  if (!msg) {
    return;
  }
  // device
  rosidl_runtime_c__String__fini(&msg->device);
  // channel
  // id
  // command_type
  // mode_type
}

bool
motor_interfaces__msg__MotorCommand__are_equal(const motor_interfaces__msg__MotorCommand * lhs, const motor_interfaces__msg__MotorCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // device
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->device), &(rhs->device)))
  {
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
  // command_type
  if (lhs->command_type != rhs->command_type) {
    return false;
  }
  // mode_type
  if (lhs->mode_type != rhs->mode_type) {
    return false;
  }
  return true;
}

bool
motor_interfaces__msg__MotorCommand__copy(
  const motor_interfaces__msg__MotorCommand * input,
  motor_interfaces__msg__MotorCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // device
  if (!rosidl_runtime_c__String__copy(
      &(input->device), &(output->device)))
  {
    return false;
  }
  // channel
  output->channel = input->channel;
  // id
  output->id = input->id;
  // command_type
  output->command_type = input->command_type;
  // mode_type
  output->mode_type = input->mode_type;
  return true;
}

motor_interfaces__msg__MotorCommand *
motor_interfaces__msg__MotorCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_interfaces__msg__MotorCommand * msg = (motor_interfaces__msg__MotorCommand *)allocator.allocate(sizeof(motor_interfaces__msg__MotorCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motor_interfaces__msg__MotorCommand));
  bool success = motor_interfaces__msg__MotorCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motor_interfaces__msg__MotorCommand__destroy(motor_interfaces__msg__MotorCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motor_interfaces__msg__MotorCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motor_interfaces__msg__MotorCommand__Sequence__init(motor_interfaces__msg__MotorCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_interfaces__msg__MotorCommand * data = NULL;

  if (size) {
    data = (motor_interfaces__msg__MotorCommand *)allocator.zero_allocate(size, sizeof(motor_interfaces__msg__MotorCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motor_interfaces__msg__MotorCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motor_interfaces__msg__MotorCommand__fini(&data[i - 1]);
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
motor_interfaces__msg__MotorCommand__Sequence__fini(motor_interfaces__msg__MotorCommand__Sequence * array)
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
      motor_interfaces__msg__MotorCommand__fini(&array->data[i]);
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

motor_interfaces__msg__MotorCommand__Sequence *
motor_interfaces__msg__MotorCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_interfaces__msg__MotorCommand__Sequence * array = (motor_interfaces__msg__MotorCommand__Sequence *)allocator.allocate(sizeof(motor_interfaces__msg__MotorCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motor_interfaces__msg__MotorCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motor_interfaces__msg__MotorCommand__Sequence__destroy(motor_interfaces__msg__MotorCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motor_interfaces__msg__MotorCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motor_interfaces__msg__MotorCommand__Sequence__are_equal(const motor_interfaces__msg__MotorCommand__Sequence * lhs, const motor_interfaces__msg__MotorCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motor_interfaces__msg__MotorCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motor_interfaces__msg__MotorCommand__Sequence__copy(
  const motor_interfaces__msg__MotorCommand__Sequence * input,
  motor_interfaces__msg__MotorCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motor_interfaces__msg__MotorCommand);
    motor_interfaces__msg__MotorCommand * data =
      (motor_interfaces__msg__MotorCommand *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motor_interfaces__msg__MotorCommand__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          motor_interfaces__msg__MotorCommand__fini(&data[i]);
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
    if (!motor_interfaces__msg__MotorCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
