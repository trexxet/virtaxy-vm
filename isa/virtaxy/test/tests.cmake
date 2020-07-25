set(ASM_OUTPUT ${CMAKE_BINARY_DIR}/test.vo)

add_asm_test(NAME asm::cmpWithZero SRC examples/cmpWithZero.vasm OUT ${ASM_OUTPUT})

