#pragma once
#include "errors.h"


typedef struct {
	int64_t opcode;
	int64_t arg1;
	int64_t arg2;
} instruction;

typedef struct {
	instruction* ops;
	uint64_t size;
	uint64_t maxSize;
} program;


_ERRNO_T asmInit(program *P);
_ERRNO_T assembleString(char *sourceStr, program *P, char *errStr);

