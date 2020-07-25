set(ASM_OUTPUT ${CMAKE_BINARY_DIR}/test.vo)

add_asm_test(NAME asm::cmpWithZero SRC examples/cmpWithZero.vasm OUT ${ASM_OUTPUT})
add_vm_test(NAME vm::cmpWithZero_-1 FILE ${ASM_OUTPUT} INPUT -1 OUTPUT 0)
add_vm_test(NAME vm::cmpWithZero_0 FILE ${ASM_OUTPUT} INPUT 0 OUTPUT 0)
add_vm_test(NAME vm::cmpWithZero_1 FILE ${ASM_OUTPUT} INPUT 1 OUTPUT 1)

