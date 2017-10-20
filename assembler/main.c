#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "errors.h"
#include "config.h"
#include "include/asm.h"


_ERRNO_T _errno = SUCCESS;


void parseCmdLineArgs(int argc, char *argv[], char **inputFilename, char **outputFilename);
void assembleFile(char *filename);
void writeProgram(char *filename);

void parseError(_ERRNO_T _errno, char *file, size_t line, char *errStr);
void finalization();


void main(int argc, char *argv[])
{
	_errno = asmInit();
	if (_errno)
		parseError(_errno, NULL, 0, NULL);

	char *inputFilename = NULL;
	char *outputFilename = DEFAULT_OUTPUT_FILENAME;
	parseCmdLineArgs(argc, argv, &inputFilename, &outputFilename);

	assembleFile(inputFilename);
	writeProgram(outputFilename);

	finalization();
}


void assembleFile(char *filename)
{
	FILE* openedFileHandle = fopen(filename, "r");
	if (!openedFileHandle)
		parseError(CANNOT_OPEN_FILE, filename, 0, NULL);
	if (feof(openedFileHandle))
		parseError(INPUT_IS_EMPTY, filename, 0, NULL);
	
	char sourceString[SOURCE_STRING_LENGTH] = {0};
	size_t lineCounter = 0;
	char errStr[2 * SOURCE_STRING_LENGTH] = {0};
	while (fgets(sourceString, SOURCE_STRING_LENGTH, openedFileHandle) && (_errno == 0))
	{
		_errno = assembleString(sourceString, errStr);
		lineCounter++;
	}
	
	if (fclose(openedFileHandle) == EOF)
		parseError(CANNOT_CLOSE_FILE, filename, lineCounter, NULL);
	openedFileHandle = NULL;
	parseError(_errno, filename, lineCounter, _errno ? errStr : NULL);
}


void writeProgram(char *filename)
{
	extern program P;
	FILE* openedFileHandle = fopen(filename, "wb");
	if (!openedFileHandle)
		parseError(CANNOT_OPEN_FILE, filename, 0, NULL);
	fwrite(&P.size, sizeof(uint64_t), 1, openedFileHandle);
	for (uint64_t i = 0; i < P.size; i++)
	{
		fwrite(&P.ops[i].opcode, sizeof(uint64_t), 1, openedFileHandle);
		fwrite(&P.ops[i].arg1, sizeof(uint64_t), 1, openedFileHandle);
		fwrite(&P.ops[i].arg2, sizeof(uint64_t), 1, openedFileHandle);
	}
	if (fclose(openedFileHandle) == EOF)
		parseError(CANNOT_CLOSE_FILE, filename, 0, NULL);
	openedFileHandle = NULL;
}


void parseCmdLineArgs(int argc, char *argv[], char **inputFilename, char **outputFilename)
{
	int opt;
	opterr = 0;
	while ((opt = getopt(argc, argv, COMMAND_LINE_OPTIONS)) != -1)
		switch (opt)
		{
			case 'o':
				*outputFilename = optarg;
				break;
			default:
			case '?':
				parseError(INCORRECT_COMMAND_LINE, NULL, 0, NULL);
				break;
		}
	if (argc - optind == 0)
		parseError(NO_INPUT_FILES, NULL, 0, NULL);
	*inputFilename = argv[optind];
}


void parseError(_ERRNO_T _errno, char *file, size_t line, char *errStr)
{
	fprintf((_errno == SUCCESS) ? stdout : stderr, 
	                              "%s:%zu: %s\n", file, line, errmsg[_errno]);
	if (errStr)
		fprintf(stderr, "%s\n", errStr);
	if (_errno != SUCCESS)
		finalization();
}


//Here we free all dynamically allocated memory, pray the Valgrind
_Noreturn void finalization()
{
	asmFinal();
	exit(_errno);
}

