cmake_minimum_required(VERSION 3.8)
project(motor_interfaces)

find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/MotorCommand.msg"
  "msg/MotorStatus.msg"
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()