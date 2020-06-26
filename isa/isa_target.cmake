# Add target to run ISA code generators

set(GENERATOR_PATH "${CMAKE_SOURCE_DIR}/generators")
set(GENERATED_PATH "${CMAKE_SOURCE_DIR}/generated/${ARCH}")

set(OPCODES_H "${GENERATED_PATH}/opcodes.h")
set(REGISTERS_H "${GENERATED_PATH}/registers.h")
set(ASSEMBLER_C "${GENERATED_PATH}/assembler.c")
set(MACHINE_C "${GENERATED_PATH}/machine.c")

set(OPCODES_GEN "${GENERATOR_PATH}/gen_opcodes.py")
set(REGISTERS_GEN "${GENERATOR_PATH}/gen_registers.py")
set(ASSEMBLER_GEN "${GENERATOR_PATH}/gen_assembler.py")
set(MACHINE_GEN "${GENERATOR_PATH}/gen_machine.py")

# Generate opcodes
add_custom_command(
	OUTPUT ${OPCODES_H}
	DEPENDS ${ISA_SRC} ${OPCODES_GEN}
	WORKING_DIRECTORY ${GENERATOR_PATH}
	COMMAND $<TARGET_FILE:Python3::Interpreter> ${OPCODES_GEN} ${ARCH} ${ISA_SRC}
)

# Generate register table
add_custom_command(
	OUTPUT ${REGISTERS_H}
	DEPENDS ${REGISTERS_SRC} ${REGISTERS_GEN}
	WORKING_DIRECTORY ${GENERATOR_PATH}
	COMMAND $<TARGET_FILE:Python3::Interpreter> ${REGISTERS_GEN} ${ARCH} ${REGISTERS_SRC}
)

# Generate assembler code
add_custom_command(
	OUTPUT ${ASSEMBLER_C}
	DEPENDS ${OPCODES_H} ${ASSEMBLER_GEN}
	WORKING_DIRECTORY ${GENERATOR_PATH}
	COMMAND $<TARGET_FILE:Python3::Interpreter> ${ASSEMBLER_GEN} ${ARCH}
)

# Generate machine code
add_custom_command(
	OUTPUT ${MACHINE_C}
	DEPENDS ${OPCODES_H} ${ISA_SRC} ${MACHINE_GEN}
	WORKING_DIRECTORY ${GENERATOR_PATH}
	COMMAND $<TARGET_FILE:Python3::Interpreter> ${MACHINE_GEN} ${ARCH} ${ISA_SRC}
)

add_custom_target(${ARCH} ALL
	DEPENDS ${OPCODES_H} ${REGISTERS_H} ${ASSEMBLER_C} ${MACHINE_C}
)

