cmake_minimum_required(VERSION 3.12)

project(virtaxy-vm)

set(VERSION "1.0")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

find_package(Python3 COMPONENTS Interpreter REQUIRED)

enable_testing()

add_subdirectory(isa)
add_subdirectory(assembler)
add_subdirectory(machine)

