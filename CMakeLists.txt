cmake_minimum_required(VERSION 2.8.3)
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
else()
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
else()
	target_link_libraries(serial setupapi)
endif()

## Uncomment for example
add_executable(${PROJECT_NAME} main.cpp)
add_dependencies(${PROJECT_NAME} serial)
target_link_libraries(${PROJECT_NAME} serial)

## Include headers
include_directories(serial/include)
