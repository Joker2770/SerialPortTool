cmake_minimum_required(VERSION 2.8.12)

if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "My multi config types" FORCE)
elseif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RELEASE)
endif()

set(CMAKE_C_FLAGS, "-Wall")
set(CMAKE_CXX_FLAGS, "-Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(SerialPortTool)

if(APPLE)
	find_library(IOKIT_LIBRARY IOKit)
	find_library(FOUNDATION_LIBRARY Foundation)
endif()

## Sources
set(serial_SRCS
	serial/src/serial.cc
	serial/include/serial/serial.h
	serial/include/serial/v8stdint.h
)
if(APPLE)
	# If OSX
	list(APPEND serial_SRCS serial/src/impl/unix.cc)
	list(APPEND serial_SRCS serial/src/impl/list_ports/list_ports_osx.cc)
elseif(UNIX)
	# If unix
	list(APPEND serial_SRCS serial/src/impl/unix.cc)
	list(APPEND serial_SRCS serial/src/impl/list_ports/list_ports_linux.cc)
elseif(MSVC)
	# If windows
	list(APPEND serial_SRCS serial/src/impl/win.cc)
	list(APPEND serial_SRCS serial/src/impl/list_ports/list_ports_win.cc)
endif()

## Add serial library
add_library(serial ${serial_SRCS})
if(APPLE)
	target_link_libraries(serial ${FOUNDATION_LIBRARY} ${IOKIT_LIBRARY})
elseif(UNIX)
	target_link_libraries(serial rt pthread)
elseif(MSVC)
	target_link_libraries(serial setupapi)
endif()

## Include headers
include_directories(serial/include)

## SerialPortTool 
file(GLOB SerialPortTool_SRCS "${CMAKE_SOURCE_DIR}/sptsrc/*.cpp" "${CMAKE_SOURCE_DIR}/sptsrc/*.h")
add_executable(${PROJECT_NAME} ${SerialPortTool_SRCS})
add_dependencies(${PROJECT_NAME} serial)
target_link_libraries(${PROJECT_NAME} serial)

# Install
if(UNIX)
	set(CMAKE_INSTALL_PREFIX /usr/local)
	install(TARGETS ${PROJECT_NAME} DESTINATION bin)
elseif(MSVC)
	set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/")
	install(TARGETS ${PROJECT_NAME} DESTINATION SerialPortTool)
endif()

