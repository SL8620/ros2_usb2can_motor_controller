// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motor_interfaces:msg/MotorControl.idl
// generated code does not contain a copyright notice
#include "motor_interfaces/msg/detail/motor_control__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `device`
#include "rosidl_runtime_c/string_functions.h"

bool
motor_interfaces__msg__MotorControl__init(motor_interfaces__msg__MotorControl * msg)
{
  if (!msg) {
    return false;
  }
  // device
  if (!rosidl_runtime_c__String__init(&msg->device)) {
    motor_interfaces__msg__MotorControl__fini(msg);
    return false;
  }
  // channel
  // id
  // position
  // velocity
  // torque
  // kp
  // kd
  return true;
}

void
motor_interfaces__msg__MotorControl__fini(motor_interfaces__msg__MotorControl * msg)
{
  if (!msg) {
    return;
  }
  // device
  rosidl_runtime_c__String__fini(&msg->device);
  // channel
  // id
  // position
  // velocity
  // torque
  // kp
  // kd
}

bool
motor_interfaces__msg__MotorControl__are_equal(const motor_interfaces__msg__MotorControl * lhs, const motor_interfaces__msg__MotorControl * rhs)
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
  // position
  if (lhs->position != rhs->position) {
    return false;
  }
  // velocity
  if (lhs->velocity != rhs->velocity) {
    return false;
  }
  // torque
  if (lhs->torque != rhs->torque) {
    return false;
  }
  // kp
  if (lhs->kp != rhs->kp) {
    return false;
  }
  // kd
  if (lhs->kd != rhs->kd) {
    return false;
  }
  return true;
}

bool
motor_interfaces__msg__MotorControl__copy(
  const motor_interfaces__msg__MotorControl * input,
  motor_interfaces__msg__MotorControl * output)
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
  // position
  output->position = input->position;
  // velocity
  output->velocity = input->velocity;
  // torque
  output->torque = input->torque;
  // kp
  output->kp = input->kp;
  // kd
  output->kd = input->kd;
  return true;
}

motor_interfaces__msg__MotorControl *
motor_interfaces__msg__MotorControl__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_interfaces__msg__MotorControl * msg = (motor_interfaces__msg__MotorControl *)allocator.allocate(sizeof(motor_interfaces__msg__MotorControl), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motor_interfaces__msg__MotorControl));
  bool success = motor_interfaces__msg__MotorControl__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motor_interfaces__msg__MotorControl__destroy(motor_interfaces__msg__MotorControl * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motor_interfaces__msg__MotorControl__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motor_interfaces__msg__MotorControl__Sequence__init(motor_interfaces__msg__MotorControl__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_interfaces__msg__MotorControl * data = NULL;

  if (size) {
    data = (motor_interfaces__msg__MotorControl *)allocator.zero_allocate(size, sizeof(motor_interfaces__msg__MotorControl), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motor_interfaces__msg__MotorControl__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motor_interfaces__msg__MotorControl__fini(&data[i - 1]);
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
motor_interfaces__msg__MotorControl__Sequence__fini(motor_interfaces__msg__MotorControl__Sequence * array)
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
      motor_interfaces__msg__MotorControl__fini(&array->data[i]);
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

motor_interfaces__msg__MotorControl__Sequence *
motor_interfaces__msg__MotorControl__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_interfaces__msg__MotorControl__Sequence * array = (motor_interfaces__msg__MotorControl__Sequence *)allocator.allocate(sizeof(motor_interfaces__msg__MotorControl__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motor_interfaces__msg__MotorControl__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motor_interfaces__msg__MotorControl__Sequence__destroy(motor_interfaces__msg__MotorControl__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motor_interfaces__msg__MotorControl__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motor_interfaces__msg__MotorControl__Sequence__are_equal(const motor_interfaces__msg__MotorControl__Sequence * lhs, const motor_interfaces__msg__MotorControl__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motor_interfaces__msg__MotorControl__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motor_interfaces__msg__MotorControl__Sequence__copy(
  const motor_interfaces__msg__MotorControl__Sequence * input,
  motor_interfaces__msg__MotorControl__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motor_interfaces__msg__MotorControl);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motor_interfaces__msg__MotorControl * data =
      (motor_interfaces__msg__MotorControl *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motor_interfaces__msg__MotorControl__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motor_interfaces__msg__MotorControl__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motor_interfaces__msg__MotorControl__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
