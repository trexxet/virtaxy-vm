// asm.c header

#pragma once

#include "errors.h"


typedef struct {
	uint64_t opcode;
	int64_t arg1;
	int64_t arg2;
} instruction;

typedef struct {
	instruction* ops;
	uint64_t size;
	uint64_t maxSize;
} program;


_ERRNO_T asmInit();
_ERRNO_T assembleString(char *sourceStr, char *errStr);
void asmFinal();

