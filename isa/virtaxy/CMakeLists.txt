cmake_minimum_required(VERSION 3.12)

set(ARCH "virtaxy")
set(ISA_SRC "ISA.txt")
set(REGISTERS_SRC "Registers.txt")
include("../isa_target.cmake")
include("test/tests.cmake")

