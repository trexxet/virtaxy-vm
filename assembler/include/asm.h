#pragma once
#include "errors.h"

typedef struct {
	uint8_t* ops;
	size_t size;
	size_t maxSize;
} program;


_ERRNO_T asmInit(program *P);
int registerNumber(char* arg);
_ERRNO_T assembleString(char *sourceStr, program *P);

