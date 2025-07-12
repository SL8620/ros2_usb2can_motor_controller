// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from motor_interfaces:msg/MotorCommand.idl
// generated code does not contain a copyright notice
#include "motor_interfaces/msg/detail/motor_command__rosidl_typesupport_fastrtps_cpp.hpp"
#include "motor_interfaces/msg/detail/motor_command__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace motor_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motor_interfaces
cdr_serialize(
  const motor_interfaces::msg::MotorCommand & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: device
  cdr << ros_message.device;
  // Member: channel
  cdr << ros_message.channel;
  // Member: id
  cdr << ros_message.id;
  // Member: position
  cdr << ros_message.position;
  // Member: velocity
  cdr << ros_message.velocity;
  // Member: time_ms
  cdr << ros_message.time_ms;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motor_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  motor_interfaces::msg::MotorCommand & ros_message)
{
  // Member: device
  cdr >> ros_message.device;

  // Member: channel
  cdr >> ros_message.channel;

  // Member: id
  cdr >> ros_message.id;

  // Member: position
  cdr >> ros_message.position;

  // Member: velocity
  cdr >> ros_message.velocity;

  // Member: time_ms
  cdr >> ros_message.time_ms;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motor_interfaces
get_serialized_size(
  const motor_interfaces::msg::MotorCommand & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: device
  {
    size_t item_size = sizeof(ros_message.device);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: channel
  {
    size_t item_size = sizeof(ros_message.channel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: id
  {
    size_t item_size = sizeof(ros_message.id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: position
  {
    size_t item_size = sizeof(ros_message.position);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: velocity
  {
    size_t item_size = sizeof(ros_message.velocity);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: time_ms
  {
    size_t item_size = sizeof(ros_message.time_ms);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motor_interfaces
max_serialized_size_MotorCommand(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: device
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: channel
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: id
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: position
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: velocity
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: time_ms
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  return current_alignment - initial_alignment;
}

static bool _MotorCommand__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const motor_interfaces::msg::MotorCommand *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _MotorCommand__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<motor_interfaces::msg::MotorCommand *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _MotorCommand__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const motor_interfaces::msg::MotorCommand *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _MotorCommand__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_MotorCommand(full_bounded, 0);
}

static message_type_support_callbacks_t _MotorCommand__callbacks = {
  "motor_interfaces::msg",
  "MotorCommand",
  _MotorCommand__cdr_serialize,
  _MotorCommand__cdr_deserialize,
  _MotorCommand__get_serialized_size,
  _MotorCommand__max_serialized_size
};

static rosidl_message_type_support_t _MotorCommand__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_MotorCommand__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace motor_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_motor_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<motor_interfaces::msg::MotorCommand>()
{
  return &motor_interfaces::msg::typesupport_fastrtps_cpp::_MotorCommand__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, motor_interfaces, msg, MotorCommand)() {
  return &motor_interfaces::msg::typesupport_fastrtps_cpp::_MotorCommand__handle;
}

#ifdef __cplusplus
}
#endif
