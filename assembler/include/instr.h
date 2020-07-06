// Instruction type

#pragma once

#include "arg_type.h"
#include "errors.h"


typedef int (*instr_encoder_t) (arg_t*, errcode_t*);

typedef struct {
	const char* str;
	argType argtypes[MAX_ARGS]; // argtypes[0] always NONE, as arg[0] is instr itself
	instr_encoder_t encoder;
} instr_t;

