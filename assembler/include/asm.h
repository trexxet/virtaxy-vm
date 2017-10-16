#pragma once
#include "errors.h"

typedef struct {
	int64_t* ops;
	uint64_t size;
	uint64_t maxSize;
} program;


_ERRNO_T asmInit(program *P);
int registerNumber(char* arg);
_ERRNO_T assembleString(char *sourceStr, program *P, char *errStr);

