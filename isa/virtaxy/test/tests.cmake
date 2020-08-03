set(ASM_OUTPUT ${CMAKE_BINARY_DIR}/test.vo)

add_asm_test(NAME asm::asmExpressions FILE examples/asmExpressions.vasm OUTPUT ${ASM_OUTPUT})
add_vm_test(NAME vm::asmExpressions FILE ${ASM_OUTPUT} OUTPUT "1\n3\n3\n7\n42")

add_asm_test(NAME asm::cmpWithZero FILE examples/cmpWithZero.vasm OUTPUT ${ASM_OUTPUT})
add_vm_test(NAME vm::cmpWithZero_-1 FILE ${ASM_OUTPUT} INPUT "-1" OUTPUT "0")
add_vm_test(NAME vm::cmpWithZero_0 FILE ${ASM_OUTPUT} INPUT "0" OUTPUT "0")
add_vm_test(NAME vm::cmpWithZero_1 FILE ${ASM_OUTPUT} INPUT "1" OUTPUT "1")

add_asm_test(NAME asm::factorialRecursive FILE examples/factorialRecursive.vasm OUTPUT ${ASM_OUTPUT})
add_vm_test(NAME vm::factorialRecursive_-1 FILE ${ASM_OUTPUT} INPUT "-1" OUTPUT "1")
add_vm_test(NAME vm::factorialRecursive_0 FILE ${ASM_OUTPUT} INPUT "0" OUTPUT "1")
add_vm_test(NAME vm::factorialRecursive_1 FILE ${ASM_OUTPUT} INPUT "1" OUTPUT "1")
add_vm_test(NAME vm::factorialRecursive_5 FILE ${ASM_OUTPUT} INPUT "5" OUTPUT "120")

add_asm_test(NAME asm::loopSum FILE examples/loopSum.vasm OUTPUT ${ASM_OUTPUT})
add_vm_test(NAME vm::loopSum_-1 FILE ${ASM_OUTPUT} INPUT "-1" OUTPUT "0")
add_vm_test(NAME vm::loopSum_0 FILE ${ASM_OUTPUT} INPUT "0 0" OUTPUT "0")
add_vm_test(NAME vm::loopSum_5 FILE ${ASM_OUTPUT} INPUT "5 1 2 3 -1 0" OUTPUT "5")

add_asm_test(NAME asm::loopSumArray FILE examples/loopSumArray.vasm OUTPUT ${ASM_OUTPUT})
add_vm_test(NAME vm::loopSumArray_-1 FILE ${ASM_OUTPUT} INPUT "-1" OUTPUT "0")
add_vm_test(NAME vm::loopSumArray_0 FILE ${ASM_OUTPUT} INPUT "0" OUTPUT "0")
add_vm_test(NAME vm::loopSumArray_10 FILE ${ASM_OUTPUT} INPUT "10 -1 -1 -1 -1 -1 -1 -1 -1 1 0" OUTPUT "-7")
add_vm_test(NAME vm::loopSumArray_11 FILE ${ASM_OUTPUT} INPUT "11" OUTPUT "-1")

add_asm_test(NAME asm::invalidFile FILE howtoexist OUTPUT ${ASM_OUTPUT} WILL_FAIL)
add_asm_test(NAME asm::invalidInstr FILE test/invalidInstr.vasm OUTPUT ${ASM_OUTPUT} WILL_FAIL)
add_asm_test(NAME asm::invalidArgs FILE test/invalidArgs.vasm OUTPUT ${ASM_OUTPUT} WILL_FAIL)
add_asm_test(NAME asm::invalidSymbol FILE test/invalidSymbol.vasm OUTPUT ${ASM_OUTPUT} WILL_FAIL)

add_asm_test(NAME asm::invalidExpr_badToken FILE test/invalidExpr_badToken.vasm OUTPUT ${ASM_OUTPUT} WILL_FAIL)
add_asm_test(NAME asm::invalidExpr_divBy0 FILE test/invalidExpr_divBy0.vasm OUTPUT ${ASM_OUTPUT} WILL_FAIL)

