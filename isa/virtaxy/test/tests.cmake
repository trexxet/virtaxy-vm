set(ASM_OUTPUT ${CMAKE_BINARY_DIR}/test.vo)

add_asm_test(asm::cmpWithZero examples/cmpWithZero.vasm ${ASM_OUTPUT} YES)

