// Instruction type

#pragma once

#include "arg_type.h"
#include "errors.h"


typedef int (*instr_encoder_t) (arg_t*, errcode_t*);

typedef struct {
	const char* str;
	instr_encoder_t encoder;
} instr_t;


instr_t* getInstr(const char* str, const instr_t* instrTable, size_t instrTableSize);

#define IS_INSTR(str) (getInstr(str, instrTable, sizeof(instrTable)/sizeof(instr_t)))

