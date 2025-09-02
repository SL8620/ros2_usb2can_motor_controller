// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motor_interfaces:msg/MotorControl.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_INTERFACES__MSG__DETAIL__MOTOR_CONTROL__STRUCT_HPP_
#define MOTOR_INTERFACES__MSG__DETAIL__MOTOR_CONTROL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__motor_interfaces__msg__MotorControl __attribute__((deprecated))
#else
# define DEPRECATED__motor_interfaces__msg__MotorControl __declspec(deprecated)
#endif

namespace motor_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorControl_
{
  using Type = MotorControl_<ContainerAllocator>;

  explicit MotorControl_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->device = "";
      this->channel = 0;
      this->id = 0;
      this->position = 0.0f;
      this->velocity = 0.0f;
      this->torque = 0.0f;
      this->kp = 0.0f;
      this->kd = 0.0f;
    }
  }

  explicit MotorControl_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : device(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->device = "";
      this->channel = 0;
      this->id = 0;
      this->position = 0.0f;
      this->velocity = 0.0f;
      this->torque = 0.0f;
      this->kp = 0.0f;
      this->kd = 0.0f;
    }
  }

  // field types and members
  using _device_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
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
  using _torque_type =
    float;
  _torque_type torque;
  using _kp_type =
    float;
  _kp_type kp;
  using _kd_type =
    float;
  _kd_type kd;

  // setters for named parameter idiom
  Type & set__device(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
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
  Type & set__torque(
    const float & _arg)
  {
    this->torque = _arg;
    return *this;
  }
  Type & set__kp(
    const float & _arg)
  {
    this->kp = _arg;
    return *this;
  }
  Type & set__kd(
    const float & _arg)
  {
    this->kd = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motor_interfaces::msg::MotorControl_<ContainerAllocator> *;
  using ConstRawPtr =
    const motor_interfaces::msg::MotorControl_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motor_interfaces::msg::MotorControl_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motor_interfaces::msg::MotorControl_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motor_interfaces::msg::MotorControl_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motor_interfaces::msg::MotorControl_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motor_interfaces::msg::MotorControl_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motor_interfaces::msg::MotorControl_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motor_interfaces::msg::MotorControl_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motor_interfaces::msg::MotorControl_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motor_interfaces__msg__MotorControl
    std::shared_ptr<motor_interfaces::msg::MotorControl_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motor_interfaces__msg__MotorControl
    std::shared_ptr<motor_interfaces::msg::MotorControl_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorControl_ & other) const
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
    if (this->torque != other.torque) {
      return false;
    }
    if (this->kp != other.kp) {
      return false;
    }
    if (this->kd != other.kd) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorControl_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorControl_

// alias to use template instance with default allocator
using MotorControl =
  motor_interfaces::msg::MotorControl_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motor_interfaces

#endif  // MOTOR_INTERFACES__MSG__DETAIL__MOTOR_CONTROL__STRUCT_HPP_
