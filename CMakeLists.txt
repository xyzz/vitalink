cmake_minimum_required(VERSION 2.8.11)
project(vitalink)

add_definitions("-std=c++0x")

include_directories(deps)

add_executable(vitalink
	src/elf.cpp
	src/stubs.cpp
	src/vitalink.cpp
	src/utility.cpp
)
INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/vitalink DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
