# Add target to run ISA code generators & tests functions

set(GENERATOR_PATH "${CMAKE_SOURCE_DIR}/generators")
set(GENERATED_PATH "${CMAKE_SOURCE_DIR}/generated/${ARCH}")

set(OPCODES_H "${GENERATED_PATH}/opcodes.h")
set(REGISTERS_H "${GENERATED_PATH}/registers.h")
set(ASM_INSTR_C "${GENERATED_PATH}/asm_instr-gen.c")
set(MACHINE_C "${GENERATED_PATH}/machine-gen.c")

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
	OUTPUT ${ASM_INSTR_C}
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

# Add ISA target
add_custom_target(isa-${ARCH} DEPENDS
	${OPCODES_H}
	${REGISTERS_H}
	${ASM_INSTR_C}
	${MACHINE_C}
)

# Tests
function(add_asm_test)
	cmake_parse_arguments(TEST "WILL_FAIL" "NAME;SRC;OUT" "" ${ARGN})
	add_test(
		NAME ${TEST_NAME}
		COMMAND sh -c "$<TARGET_FILE:vasm-${ARCH}> -o ${TEST_OUT} ${TEST_SRC}"
	)
	set_tests_properties(
		${TEST_NAME} PROPERTIES
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		WILL_FAIL ${TEST_WILL_FAIL}
	)
	if(NOT ${TEST_WILL_FAIL})
		set_tests_properties(
			${TEST_NAME} PROPERTIES
			PASS_REGULAR_EXPRESSION "Assembly successful"
		)
	endif()
endfunction()

function(add_vm_test)
	cmake_parse_arguments(TEST "WILL_FAIL" "NAME;FILE;INPUT;OUTPUT" "" ${ARGN})
	add_test(
		NAME ${TEST_NAME}
		COMMAND sh -c "echo ${TEST_INPUT} | $<TARGET_FILE:vvm-${ARCH}> ${TEST_FILE}"
	)
	set_tests_properties(
		${TEST_NAME} PROPERTIES
		WILL_FAIL ${TEST_WILL_FAIL}
	)
	if(NOT ${TEST_WILL_FAIL})
		set_tests_properties(
			${TEST_NAME} PROPERTIES
			PASS_REGULAR_EXPRESSION "${TEST_OUTPUT}\n.*Execution successful"
		)
	endif()
endfunction()

