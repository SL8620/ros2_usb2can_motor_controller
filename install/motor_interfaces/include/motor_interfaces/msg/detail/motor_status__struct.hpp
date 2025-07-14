// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motor_interfaces:msg/MotorStatus.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_INTERFACES__MSG__DETAIL__MOTOR_STATUS__STRUCT_HPP_
#define MOTOR_INTERFACES__MSG__DETAIL__MOTOR_STATUS__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__motor_interfaces__msg__MotorStatus __attribute__((deprecated))
#else
# define DEPRECATED__motor_interfaces__msg__MotorStatus __declspec(deprecated)
#endif

namespace motor_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorStatus_
{
  using Type = MotorStatus_<ContainerAllocator>;

  explicit MotorStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->device = "";
      this->channel = 0;
      this->id = 0;
      this->current_position = 0.0f;
      this->current_velocity = 0.0f;
      this->current_torque = 0.0f;
    }
  }

  explicit MotorStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : device(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->device = "";
      this->channel = 0;
      this->id = 0;
      this->current_position = 0.0f;
      this->current_velocity = 0.0f;
      this->current_torque = 0.0f;
    }
  }

  // field types and members
  using _device_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _device_type device;
  using _channel_type =
    uint8_t;
  _channel_type channel;
  using _id_type =
    uint8_t;
  _id_type id;
  using _current_position_type =
    float;
  _current_position_type current_position;
  using _current_velocity_type =
    float;
  _current_velocity_type current_velocity;
  using _current_torque_type =
    float;
  _current_torque_type current_torque;

  // setters for named parameter idiom
  Type & set__device(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
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
  Type & set__current_position(
    const float & _arg)
  {
    this->current_position = _arg;
    return *this;
  }
  Type & set__current_velocity(
    const float & _arg)
  {
    this->current_velocity = _arg;
    return *this;
  }
  Type & set__current_torque(
    const float & _arg)
  {
    this->current_torque = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motor_interfaces::msg::MotorStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const motor_interfaces::msg::MotorStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motor_interfaces::msg::MotorStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motor_interfaces::msg::MotorStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motor_interfaces::msg::MotorStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motor_interfaces::msg::MotorStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motor_interfaces::msg::MotorStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motor_interfaces::msg::MotorStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motor_interfaces::msg::MotorStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motor_interfaces::msg::MotorStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motor_interfaces__msg__MotorStatus
    std::shared_ptr<motor_interfaces::msg::MotorStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motor_interfaces__msg__MotorStatus
    std::shared_ptr<motor_interfaces::msg::MotorStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorStatus_ & other) const
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
    if (this->current_position != other.current_position) {
      return false;
    }
    if (this->current_velocity != other.current_velocity) {
      return false;
    }
    if (this->current_torque != other.current_torque) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorStatus_

// alias to use template instance with default allocator
using MotorStatus =
  motor_interfaces::msg::MotorStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motor_interfaces

#endif  // MOTOR_INTERFACES__MSG__DETAIL__MOTOR_STATUS__STRUCT_HPP_
