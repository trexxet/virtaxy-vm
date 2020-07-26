// Symbol table types & functions

#pragma once

#include <stdint.h>
#include "errors.h"
#include "../config.h"


typedef struct {
	char name[SOURCE_STRING_LENGTH];
	YYSTYPE value;
} symbol;

typedef struct {
	symbol* sym;
	uint64_t size;
	uint64_t maxSize;
} symTable;


errcode_t symInit(symTable* S);
void symAdd(symTable* S, char* name, YYSTYPE value);
int symGetValue(symTable* S, char* name, YYSTYPE* value);
void symDestroy(symTable* S);

// Debug:
void symPrint(symTable* S);

