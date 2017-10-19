// Macros for assembling

#define LOAD_ARG(arg)                   \
	arg.str = strtok(NULL, DELIM);  \
	arg.type = IS_NUM(arg.str) + IS_REG(arg.str) * 2;

#define CHECK_PROGRAM_SIZE(incsize)                          \
	if (P->maxSize - P->size < incsize)                  \
		P->ops = (instruction *) realloc(P->ops,     \
			  (P->maxSize += P->maxSize * 2) * sizeof(instruction))

#define IF_INSTR(instr) if (strcmp(instrStr, #instr) == 0)

#define OPCODE P->ops[P->size].opcode
#define ARG1   P->ops[P->size].arg1
#define ARG2   P->ops[P->size].arg2

#define IS_REG2(arg) (arg && strlen(arg) == 2 &&          \
		      strchr(REGISTER_POSTFIX, arg[1]) && \
		      strchr(REGISTER_LETTER, arg[0]))

#define IS_REG3(arg) (arg && strlen(arg) == 3 &&         \
		      arg[2] == REGISTER_POSTFIX[0] &&   \
		      strchr(REGISTER_PREFIX, arg[0]) && \
		      strchr(REGISTER_LETTER, arg[1]))

#define IS_REG(arg) (IS_REG2(arg) || IS_REG3(arg))

#define REG_NUM(arg) registerNumber(arg)

#define IS_NUM(arg) isNum(arg)

