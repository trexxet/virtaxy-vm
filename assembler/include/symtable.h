// Symbol table types & functions

#pragma once

#include <stdint.h>
#include "errors.h"
#include "../config.h"


typedef struct {
	char name[SOURCE_STRING_LENGTH];
	int64_t value;
} symbol;

typedef struct {
	symbol* sym;
	uint64_t size;
	uint64_t maxSize;
} symTable;


_ERRNO_T symInit(symTable *S);
void symAdd(symTable *S, char *name, int64_t value);
int symGetValue(symTable *S, char *name, int64_t *value);
void symDestroy(symTable *S);

