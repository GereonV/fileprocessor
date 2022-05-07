#include <stdio.h>
#include <string.h>
#include "template.h"

#define ERR(...) fprintf(stderr, __VA_ARGS__)

typedef enum {
    ARGUMENT_VALID,
    ARGUMENT_COMPILER_REDEFINED,
    ARGUMENT_EXTENSION_REDEFINED,
    ARGUMENT_OPTION_INVALID,
    ARGUMENT_HELP
} ARGUMENT;
static const char *ERRORS_ARGUMENT[] = {
    "Compiler already defined",
    "Extension already defined",
    "not a valid Option"
};

static const char *compiler, *extension;

static ARGUMENT handleArgument(const char *const argument) {
    if(!strcmp(argument, "--help"))
        return ARGUMENT_HELP;
    if(argument[0] != '-')
        return ARGUMENT_OPTION_INVALID;
    const char **string;
    switch(argument[1]) {
        case 'C':
            if(compiler)
                return ARGUMENT_COMPILER_REDEFINED;
            string = &compiler;
            break;
        case 'E':
            if(extension)
                return ARGUMENT_EXTENSION_REDEFINED;
            string = &extension;
            break;
        default:
            return ARGUMENT_OPTION_INVALID;
    }
    *string = argument + 2;
    return ARGUMENT_VALID;
}

static inline void validateState() {
    if(!compiler)
        compiler = "gcc # default value";
    if(!extension)
        extension = "c # default value";
}

int main(const int argc, const char *const argv[]) {
    for(int argI = 1; argI < argc; argI++) {
        ARGUMENT argument = handleArgument(argv[argI]);
        switch(argument) {
            case ARGUMENT_VALID:
                continue;
            case ARGUMENT_HELP:
                printf("\n"
                    "Usage: ([-C<compiler>]) ([-E<extension>])\n"
                    "Creates a default 'Makefile'.\n"
                    "(Order of the arguments may be ignored)\n\n"
                    "compiler: Program to use as the Compiler\n"
                    "\tCommon values include 'gcc' and 'clang'\n\n"
                    "extension: File-Extension of the Source-Files\n"
                    "\tCommon values include 'c', 'cpp' and 'cc'\n"
                );
                return 0;
            default:
                ERR("Invalid Argument at position %u (%s): %s\n", argI, argv[argI], ERRORS_ARGUMENT[argument - 1]);
                return -1;
        }
    }
    validateState();
    FILE *file = fopen("Makefile", "w");
    if(!file) {
        ERR("Output-File (Makefile) couldn't be opened\n");
        return -1;
    }
    fprintf(file, TEMPLATE_MK, compiler, extension);
    fclose(file);
}
