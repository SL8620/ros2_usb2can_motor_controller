cmake_minimum_required(VERSION 3.5)
project(motor_controller)

# 设置 C++17 标准
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# 查找依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(motor_interfaces REQUIRED)
find_package(can_usb_driver REQUIRED)
find_package(yaml-cpp REQUIRED)

# 包含头文件路径
include_directories(
  include
  ${crclcpp_INCLUDE_DIRS}
  ${can_usb_driver_INCLUDE_DIRS}
  ${motor_interfaces_INCLUDE_DIRS}
)

set(SOURCES
  src/motor_node.cpp
  src/math_ops.cpp
  src/rs03_motor_parser.cpp
)

# 添加可执行文件
add_executable(motor_node ${SOURCES})

# 链接依赖库
ament_target_dependencies(motor_node
  rclcpp
  std_msgs
  motor_interfaces
  yaml-cpp
  can_usb_driver
)

target_link_libraries(motor_node yaml-cpp)

# 安装目标
install(TARGETS motor_node
  DESTINATION lib/${PROJECT_NAME}
)

# 安装头文件
install(DIRECTORY include/
  DESTINATION include
)

# 安装配置文件
install(DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config
)

# 安装launch文件
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/
)

# 导出 package
ament_package()