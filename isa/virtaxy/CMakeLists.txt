cmake_minimum_required(VERSION 3.12)

set(ARCH "virtaxy")
set(ISA_SRC "ISA.txt")
set(REGISTERS_SRC "Registers.txt")
include("../isa_target.cmake")

include("../isa_tests.cmake")
include("test/tests.cmake")

