// Register types & functions

#pragma once


#include <string.h>
#include "../generated/registers.h"


__attribute__((hot))
int regNumber(char* arg) // Returns number of register arg or -1 if doesn't exists
{
	for (int64_t i = 0; i < NUM_OF_REGISTERS; i++)
		if (strcmp(reg[i].name, arg) == 0)
			return i;
	return -1;
}

#define IS_REG(arg) ((arg && regNumber(arg) >= 0) ? REG : NONE)
#define REG_NUM(arg) regNumber(arg)

