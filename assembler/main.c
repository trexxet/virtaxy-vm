#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "errors.h"
#include "config.h"
#include "asm.h"


_ERRNO_T _errno = SUCCESS;


typedef struct {
	char *inputFilename;
	char *outputFilename;
} conf_t;


void parseCmdLineArgs(int argc, char *argv[], conf_t *conf);
void assembleFile(char *filename);
void writeProgram(char *filename);

void parseError(_ERRNO_T _errno, char *file, size_t line, char *errStr);
void finalization();


void main(int argc, char *argv[])
{
	_errno = asmInit();
	if (_errno)
		parseError(_errno, NULL, 0, NULL);

	conf_t conf = {NULL, DEFAULT_OUTPUT_FILENAME};
	parseCmdLineArgs(argc, argv, &conf);

	assembleFile(conf.inputFilename);
	writeProgram(conf.outputFilename);

	finalization();
}


void assembleFile(char *filename)
{
	FILE* openedFileHandle = fopen(filename, "r");
	if (!openedFileHandle)
		parseError(CANNOT_OPEN_FILE, filename, 0, NULL);
	if (feof(openedFileHandle))
		parseError(INPUT_IS_EMPTY, filename, 0, NULL);
	
	char sourceString[SOURCE_STRING_LENGTH + 1] = {0};
	size_t lineCounter = 0;
	char errStr[SOURCE_STRING_LENGTH + ERR_STR_LEN] = {0};
	#define STRING_NOT_EMPTY (sourceString[0] != 0) && (sourceString[0] != '\n')
	#define STRING_NOT_COMMENT (sourceString[0] != COMMENT_SYMBOL)
	extern program P; 
	for (int pass = 1; pass <= 2; pass++)
	{
		while (fgets(sourceString, SOURCE_STRING_LENGTH, openedFileHandle) &&
		       ((pass == 2) ? (_errno == 0) : 1))			
		{
			if (STRING_NOT_EMPTY && STRING_NOT_COMMENT)
				_errno = assembleString(sourceString, pass, errStr);
			if (pass == 2)
				lineCounter++;
		}
		if (pass == 1)
		{
			P.size = 0;
			rewind(openedFileHandle);
		}
	}
	#undef STRING_NOT_EMPTY
	#undef STRING_NOT_COMMENT
	
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
	for (uint64_t i = 0; i < P.size; i++)
		fwrite(&P.bytes[i], sizeof(uint64_t), 1, openedFileHandle);
	if (fclose(openedFileHandle) == EOF)
		parseError(CANNOT_CLOSE_FILE, filename, 0, NULL);
	openedFileHandle = NULL;
}


void parseCmdLineArgs(int argc, char *argv[], conf_t *conf)
{
	int opt;
	opterr = 0;
	extern int printSymtableAtFinal;
	while ((opt = getopt(argc, argv, COMMAND_LINE_OPTIONS)) != -1)
		switch (opt)
		{
			case 'o': // Set output filename
				conf -> outputFilename = optarg;
				break;
			case 's': // Print symbol table
				printSymtableAtFinal = 1;
				break;
			default:
			case '?':
				parseError(INCORRECT_COMMAND_LINE, NULL, 0, NULL);
				break;
		}
	if (argc == optind)
		parseError(NO_INPUT_FILES, NULL, 0, NULL);
	conf -> inputFilename = argv[optind];
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

