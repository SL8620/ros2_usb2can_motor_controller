cmake_minimum_required(VERSION 3.8)
project(can_usb_driver)

find_package(Threads REQUIRED)
find_package(ament_cmake REQUIRED)

add_library(can_usb_driver
  src/can_usb_device.cpp
)

target_link_libraries(can_usb_driver PRIVATE
    Threads::Threads
)

target_include_directories(can_usb_driver PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS can_usb_driver
  EXPORT export_can_usb_driver
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)

ament_export_include_directories(include)
ament_export_targets(export_can_usb_driver)
ament_package()