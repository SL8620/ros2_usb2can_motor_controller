cmake_minimum_required(VERSION 3.8)
project(motor_test)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(motor_interfaces REQUIRED)
find_package(yaml-cpp REQUIRED)

# 包含目录
include_directories(
  include
  ${rclcpp_INCLUDE_DIRS}
  ${motor_interfaces_INCLUDE_DIRS}
  ${yaml-cpp_INCLUDE_DIRS}
)

# 添加可执行文件
add_executable(motor_test_node
  src/motor_test.cpp
)

# 链接依赖
ament_target_dependencies(motor_test_node
  rclcpp
  motor_interfaces
  yaml-cpp
)

# 安装目标
install(TARGETS motor_test_node
  DESTINATION lib/${PROJECT_NAME}
)

# 安装配置文件
install(
  DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config
)

# 安装launch文件（新增）
install(
  DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch
)

# 导出ament包
ament_package()