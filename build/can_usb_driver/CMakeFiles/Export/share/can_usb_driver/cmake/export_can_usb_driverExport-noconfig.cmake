#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "can_usb_driver::can_usb_driver" for configuration ""
set_property(TARGET can_usb_driver::can_usb_driver APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(can_usb_driver::can_usb_driver PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libcan_usb_driver.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS can_usb_driver::can_usb_driver )
list(APPEND _IMPORT_CHECK_FILES_FOR_can_usb_driver::can_usb_driver "${_IMPORT_PREFIX}/lib/libcan_usb_driver.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
