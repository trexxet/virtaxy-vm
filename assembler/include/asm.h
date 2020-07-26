// asm.c header

#pragma once

#include "errors.h"


typedef struct {
	int64_t* bytes;
	uint64_t size;
	uint64_t maxSize;
} program;


errcode_t asmInit();
errcode_t assembleString(char* sourceStr, int pass, char* errStr);
void asmFinal();

