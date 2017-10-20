// Register types & functions

#pragma once

#include <string.h>
#include "../config.h"


__attribute__((hot))
int registerNumber(char* arg)  // Returns number of register arg
{
	#define _getPos(_STR_, _CHR_) (strchr(_STR_, _CHR_) - _STR_)
	if (strlen(arg) == 2)      // 2-letter register name (without prefix)
		return 	_getPos(REGISTER_LETTER, arg[0]) * NUM_OF_REGS_IN_GROUP +
		        strlen(REGISTER_PREFIX) + _getPos(REGISTER_POSTFIX, arg[1]) + 1;

	if (strlen(arg) == 3)      // 3-letter register name (without postfix)
		return _getPos(REGISTER_LETTER, arg[1]) * NUM_OF_REGS_IN_GROUP +
		       _getPos(REGISTER_PREFIX, arg[0]) + 1;
	#undef _getPos
}

#define REG_NUM(arg) registerNumber(arg)

