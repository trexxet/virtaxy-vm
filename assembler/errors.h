//This file contains error codes.

#pragma once

typedef enum { 
	SUCCESS,	
	INCORRECT_COMMAND_LINE,
	NO_INPUT_FILES,
	CANNOT_OPEN_FILE,
	CANNOT_CLOSE_FILE,
	INPUT_IS_EMPTY,
	CANNOT_ALLOCATE_MEMORY,
	UNKNOWN_COMMAND,
	INVALID_ARGS
} _ERRNO_T;

const static char* errmsg[] = {
	"Assembly successful",
	"Usage: vmm-asm file1 file2 ... -o outputFile"
	"Error: no input files",
	"Error: cannot open file",
	"Error: cannot close file",
	"Error: input file is empty",
	"Error: cannot allocate memory for program",
	"Error: unknown command",
	"Error: invalid combination of command and arguments"
};
