cmake_minimum_required(VERSION 3.10)

set(ARCH "virtaxy")

set(ISA_SRC "ISA.txt")
set(REGISTERS_SRC "Registers.txt")

set(GENERATOR_PATH "${CMAKE_SOURCE_DIR}/generators")
set(GENERATED_PATH "${CMAKE_SOURCE_DIR}/generated/${ARCH}")

set(OPCODES_H "${GENERATED_PATH}/opcodes.h")
set(REGISTERS_H "${GENERATED_PATH}/registers.h")
set(ASSEMBLER_C "${GENERATED_PATH}/assembler.c")
set(MACHINE_C "${GENERATED_PATH}/machine.c")

# Generate opcodes
add_custom_command(
	OUTPUT ${OPCODES_H}
	DEPENDS ${ISA_SRC}
	WORKING_DIRECTORY ${GENERATOR_PATH}
	COMMAND python3 gen_opcodes.py ${ARCH} ${ISA_SRC}
)

# Generate register table
add_custom_command(
	OUTPUT ${REGISTERS_H}
	DEPENDS ${REGISTERS_SRC}
	WORKING_DIRECTORY ${GENERATOR_PATH}
	COMMAND python3 gen_registers.py ${ARCH} ${REGISTERS_SRC}
)

# Generate assembler code
add_custom_command(
	OUTPUT ${ASSEMBLER_C}
	DEPENDS ${OPCODES_H}
	WORKING_DIRECTORY ${GENERATOR_PATH}
	COMMAND python3 gen_assembler.py ${ARCH}
)

# Generate machine code
add_custom_command(
	OUTPUT ${MACHINE_C}
	DEPENDS ${OPCODES_H} ${ISA_SRC}
	WORKING_DIRECTORY ${GENERATOR_PATH}
	COMMAND python3 gen_machine.py ${ARCH} ${ISA_SRC}
)

add_custom_target(${ARCH} ALL
	DEPENDS ${OPCODES_H} ${REGISTERS_H} ${ASSEMBLER_C} ${MACHINE_C}
)

