cmake_minimum_required(VERSION 3.8)
project(motor_test)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找依赖
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(motor_interfaces REQUIRED)

# yaml-cpp特殊处理
find_package(PkgConfig REQUIRED)
pkg_check_modules(YAML_CPP REQUIRED yaml-cpp)

# 包含目录
include_directories(
    include
    ${rclcpp_INCLUDE_DIRS}
    ${motor_interfaces_INCLUDE_DIRS}
    ${YAML_CPP_INCLUDE_DIRS}
)

# 添加可执行文件
add_executable(motor_test_node
    src/motor_test.cpp
)

# 链接配置 - 使用pkg-config找到的变量
target_link_libraries(motor_test_node
    ${rclcpp_LIBRARIES}
    ${motor_interfaces_LIBRARIES}
    ${YAML_CPP_LIBRARIES}
)

# 安装配置
install(TARGETS motor_test_node
    DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY config/ DESTINATION share/${PROJECT_NAME}/config)
install(DIRECTORY launch/ DESTINATION share/${PROJECT_NAME}/launch)
install(
  DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch
  PATTERN "*.launch.py"  # 明确指定只安装launch文件
)

ament_package()