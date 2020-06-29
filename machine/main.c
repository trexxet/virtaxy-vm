#define _GNU_SOURCE
#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "config.h"
#include "errors.h"
#include "machine.h"
#include "mem.h"


errcode_t errcode = SUCCESS;


typedef struct {
	char *inputFilename;
	size_t memSize;
} conf_t;


void parseCmdLineArgs(int argc, char *argv[], conf_t *conf);
void executeFile(char *filename);

void parseError(errcode_t errcode, char *file, char *errStr);
void printVersion();
void finalization();


void main(int argc, char* argv[])
{
	conf_t conf = {NULL, DEFAULT_MEMSIZE};
	parseCmdLineArgs(argc, argv, &conf);

	errcode = machineInit(conf.memSize);
	if (errcode)
		parseError(errcode, NULL, NULL);

	executeFile(conf.inputFilename);

	finalization();
}


void executeFile(char *filename)
{
	FILE* openedFileHandle = fopen(filename, "r");
	if (!openedFileHandle)
		parseError(CANNOT_OPEN_FILE, filename, NULL);
	if (feof(openedFileHandle))
		parseError(INPUT_IS_EMPTY, filename, NULL);

	extern mem_t M;
	int64_t *memPtr = M.data;
	while(fread(memPtr++, sizeof(int64_t), 1, openedFileHandle));
	errcode = machineRun();

	if (fclose(openedFileHandle) == EOF)
		parseError(CANNOT_CLOSE_FILE, filename, NULL);
	openedFileHandle = NULL;
	parseError(errcode, filename, NULL);
}


void parseCmdLineArgs(int argc, char *argv[], conf_t *conf)
{
	int opt;
	opterr = 0;
	extern struct {int reg, mem, stack;} printDump;
	extern int stepByStep;
	while ((opt = getopt(argc, argv, "M:rmsdv")) != -1)
		switch (opt)
		{
			case 'M': // Set memory size
				conf -> memSize = strtol(optarg, NULL, 0);
				break;
			case 'r': // Print registers and current opcode every cycle
				printDump.reg = 1;
				break;
			case 'm': // Print memory dump every cycle
				printDump.mem = 1;
				break;
			case 's': // Print stack dump every cycle
				printDump.stack = 1;
				break;
			case 'd': // Step-by-step execution
				stepByStep = 1;
				break;
			case 'v': // Print version
				printVersion();
				finalization();
				break;
			case '?':
			default:
				parseError(INCORRECT_COMMAND_LINE, NULL, NULL);
				break;
		}
	if (argc == optind)
		parseError(NO_INPUT_FILES, NULL, NULL);
	conf -> inputFilename = argv[optind];
}


void parseError(errcode_t errcode, char *file, char *errStr)
{
	fprintf((errcode == SUCCESS) ? stdout : stderr, "%s: %s\n", file, errmsg[errcode]);
	if (errStr)
		fprintf(stderr, "%s\n", errStr);
	if (errcode != SUCCESS)
		finalization();
}


void printVersion()
{
	printf("Virtaxy machine version %s\n", VERSION);
	printf("Arch: %s\n", ARCH);
}


//Here we free all dynamically allocated memory, pray the Valgrind
_Noreturn void finalization()
{
	machineDestroy();
	exit(errcode);
}

