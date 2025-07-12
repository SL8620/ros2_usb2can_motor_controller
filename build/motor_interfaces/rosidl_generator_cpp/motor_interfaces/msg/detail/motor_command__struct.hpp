// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motor_interfaces:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_INTERFACES__MSG__DETAIL__MOTOR_COMMAND__STRUCT_HPP_
#define MOTOR_INTERFACES__MSG__DETAIL__MOTOR_COMMAND__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__motor_interfaces__msg__MotorCommand __attribute__((deprecated))
#else
# define DEPRECATED__motor_interfaces__msg__MotorCommand __declspec(deprecated)
#endif

namespace motor_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorCommand_
{
  using Type = MotorCommand_<ContainerAllocator>;

  explicit MotorCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->device = 0;
      this->channel = 0;
      this->id = 0;
      this->position = 0.0f;
      this->velocity = 0.0f;
      this->time_ms = 0;
    }
  }

  explicit MotorCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->device = 0;
      this->channel = 0;
      this->id = 0;
      this->position = 0.0f;
      this->velocity = 0.0f;
      this->time_ms = 0;
    }
  }

  // field types and members
  using _device_type =
    uint8_t;
  _device_type device;
  using _channel_type =
    uint8_t;
  _channel_type channel;
  using _id_type =
    uint8_t;
  _id_type id;
  using _position_type =
    float;
  _position_type position;
  using _velocity_type =
    float;
  _velocity_type velocity;
  using _time_ms_type =
    uint16_t;
  _time_ms_type time_ms;

  // setters for named parameter idiom
  Type & set__device(
    const uint8_t & _arg)
  {
    this->device = _arg;
    return *this;
  }
  Type & set__channel(
    const uint8_t & _arg)
  {
    this->channel = _arg;
    return *this;
  }
  Type & set__id(
    const uint8_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__position(
    const float & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const float & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__time_ms(
    const uint16_t & _arg)
  {
    this->time_ms = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motor_interfaces::msg::MotorCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const motor_interfaces::msg::MotorCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motor_interfaces::msg::MotorCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motor_interfaces::msg::MotorCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motor_interfaces::msg::MotorCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motor_interfaces::msg::MotorCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motor_interfaces::msg::MotorCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motor_interfaces::msg::MotorCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motor_interfaces::msg::MotorCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motor_interfaces::msg::MotorCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motor_interfaces__msg__MotorCommand
    std::shared_ptr<motor_interfaces::msg::MotorCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motor_interfaces__msg__MotorCommand
    std::shared_ptr<motor_interfaces::msg::MotorCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorCommand_ & other) const
  {
    if (this->device != other.device) {
      return false;
    }
    if (this->channel != other.channel) {
      return false;
    }
    if (this->id != other.id) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->time_ms != other.time_ms) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorCommand_

// alias to use template instance with default allocator
using MotorCommand =
  motor_interfaces::msg::MotorCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motor_interfaces

#endif  // MOTOR_INTERFACES__MSG__DETAIL__MOTOR_COMMAND__STRUCT_HPP_
