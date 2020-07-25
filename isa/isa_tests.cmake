# Functions to run asm & vm tests

function(add_asm_test)
	cmake_parse_arguments(TEST "WILL_FAIL" "NAME;FILE;OUTPUT" "" ${ARGN})
	add_test(
		NAME ${TEST_NAME}
		COMMAND sh -c "$<TARGET_FILE:vasm-${ARCH}> -o ${TEST_OUTPUT} ${TEST_FILE}"
	)
	set_tests_properties(
		${TEST_NAME} PROPERTIES
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		WILL_FAIL ${TEST_WILL_FAIL}
		PASS_REGULAR_EXPRESSION "Assembly successful"
	)
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
		PASS_REGULAR_EXPRESSION "${TEST_OUTPUT}\n.*Execution successful"
	)
endfunction()

