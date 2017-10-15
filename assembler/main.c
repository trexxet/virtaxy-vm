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
program P;

void parseCmdLineArgs(int argc, char *argv[], char **inputFilename, char *outputFilename);
void assembleFile(char* filename);
void parseError(_ERRNO_T _errno, char *file, uint32_t line);
void finalization();


void main(int argc, char *argv[])
{
	_errno = asmInit(&P);
	if (_errno)
		parseError(_errno, NULL, 0);

	char *inputFilename = NULL;
	char *outputFilename = DEFAULT_OUTPUT_FILENAME;
	parseCmdLineArgs(argc, argv, &inputFilename, outputFilename);

	assembleFile(inputFilename);

	finalization();
}


void assembleFile(char *filename)
{
	FILE* openedFileHandle = fopen(filename, "r");
	if (!openedFileHandle)
		parseError(CANNOT_OPEN_FILE, filename, 0);
	if (feof(openedFileHandle))
		parseError(INPUT_IS_EMPTY, filename, 0);
	char sourceString[SOURCE_STRING_LENGTH];
	uint32_t lineCounter = 0;
	while (fgets(sourceString, SOURCE_STRING_LENGTH, openedFileHandle) && (_errno == 0))
	{
		_errno = assembleString(sourceString, &P);
		lineCounter++;
	}
	if (fclose(openedFileHandle) == EOF)
		parseError(CANNOT_CLOSE_FILE, filename, lineCounter);
	openedFileHandle = NULL;
	parseError(_errno, filename, lineCounter);
}


void parseCmdLineArgs(int argc, char *argv[], char **inputFilename, char *outputFilename)
{
	int opt;
	opterr = 0;
	while ((opt = getopt(argc, argv, COMMAND_LINE_OPTIONS)) != -1)
		switch (opt)
		{
			case 'o':
				outputFilename = optarg;
				break;
			default:
			case '?':
				parseError(INCORRECT_COMMAND_LINE, NULL, 0);
				break;
		}
	if (argc - optind == 0)
		parseError(NO_INPUT_FILES, NULL, 0);
	*inputFilename = argv[optind];
}


void parseError(_ERRNO_T _errno, char *file, uint32_t line)
{
	fprintf(stderr, "%s:%zu: %s\n", file, line, errmsg[_errno]);
	if (_errno != SUCCESS)
		finalization();
}


_Noreturn void finalization()
//Here we free all dynamically allocated memory, pray the Valgrind
{
	free(P.ops);
	exit(_errno);
}

