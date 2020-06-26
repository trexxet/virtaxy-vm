cmake_minimum_required(VERSION 3.12)

project(virtaxy-vm)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

find_package(Python3 COMPONENTS Interpreter REQUIRED)

if(NOT DEFINED ARCH)
	message(WARNING "No arch given, using virtaxy by default")
	set(ARCH "virtaxy")
endif()

add_subdirectory(isa)
add_subdirectory(assembler)
add_subdirectory(machine)

