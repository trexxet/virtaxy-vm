//Command line configuration
#define COMMAND_LINE_OPTIONS "o:"             //Command line options for getopt()
#define MAX_INPUT_FILES 64                    //Max number of input files
#define INPUT_FILENAME_MAX_LEN 64             //Max length of name of input file

//Initialisation configuration
#define DEFAULT_OUTPUT_FILENAME "a.vo"        //Default name of output file, if -o was not specified
#define SOURCE_STRING_LENGTH 128              //Max length of text string in source file
#define INIT_PROGRAM_SIZE 128                 //Initial program size in bytes

//Assembling configuration
#define DELIM " ,\n"                          // Delim for strtok_r()
#define REGISTER_PREFIX "rdeh"                // Register prefixes (rax, dax, eax, hax, or no prefix - ax)
#define REGISTER_LETTER "abcdefghjklmnopq"    // Register groups (ax, bx, cx, ...)
#define REGISTER_POSTFIX "xhl"                // Register postfixes (ax, ah, al)
#define NUM_OF_REGS_IN_GROUP 7                // strlen(REGISTER_PREFIX) + strlen(REGISTER_POSTFIX)

