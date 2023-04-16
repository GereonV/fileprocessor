#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERR(...) fprintf(stderr, __VA_ARGS__)

#define PATH_LENGTH 256
typedef struct {
    size_t length;  // with null-termination
    char string[PATH_LENGTH];
} PATH;

typedef enum {
    ARGUMENT_VALID,
    ARGUMENT_TOO_LONG,
    ARGUMENT_OUTPUT_REDEFINED,
    ARGUMENT_OPTION_INVALID,
    ARGUMENT_HELP
} ARGUMENT;
static const char *ERRORS_ARGUMENT[] = {
    "too long",
    "Output already defined",
    "not a valid Option"
};

typedef ARGUMENT (*ARG_FUNC)(const char *, size_t);

typedef enum {
    STATE_VALID,
    STATE_OUTPUT_UNDEFINED
} STATE;
static const char *ERRORS_STATE[] = {
    "no Output provided"
};

static size_t inputCount;
static PATH outputPath, *inputPaths, directoryPath = { .length = 2, .string = "."};

static void toScreamingSnakeCase(char *const string, const size_t length) {
    for(size_t i = 0; i < length; i++)
        string[i] += ('A' - 'a') * (string[i] >= 'a' && string[i] <= 'z') + ('_' - '.') * (string[i] == '.');
}

static ARGUMENT handleOutput(const char *const path, const size_t length) {
    if(length >= PATH_LENGTH)
        return ARGUMENT_TOO_LONG;
    outputPath.length = length + 1;
    strcpy(outputPath.string, path);
    return ARGUMENT_VALID;
}

static ARGUMENT handleDirectory(const char *const directory, size_t length) {
    char c = directory[length - 1];
    length -= c == '/' || c == '\\';
    if(length >= PATH_LENGTH)
        return ARGUMENT_TOO_LONG;
    directoryPath.length = length + 1;
    strncpy(directoryPath.string, directory, length);
    directoryPath.string[length] = 0;
    return ARGUMENT_VALID;
}

static inline ARGUMENT handleOption(const char *const option, const size_t length) {
    ARG_FUNC func;
    switch(option[0]) {
        case 'O':
            func = handleOutput;
            break;
        case 'D':
            func = handleDirectory;
            break;
        default:
            return ARGUMENT_OPTION_INVALID;
    }
    return func(option + 1, length - 1);
}

static ARGUMENT handleInput(const char *const path, const size_t length) {
    static size_t pathsSize = 10;
    size_t pathLength = directoryPath.length + length + 1;
    if(pathLength >= PATH_LENGTH)
        return ARGUMENT_TOO_LONG;
    if(!inputPaths)
        inputPaths = malloc(pathsSize * sizeof(PATH));
    else if(inputCount == pathsSize)
        inputPaths = realloc(inputPaths, (pathsSize <<= 1) * sizeof(PATH));
    PATH *input = inputPaths + inputCount++;
    input->length = pathLength;
    strcpy(input->string, directoryPath.string);
    input->string[directoryPath.length - 1] = '/';
    strcpy(input->string + directoryPath.length, path);
    return ARGUMENT_VALID;
}

static inline ARGUMENT handleArgument(const char *const argument) {
    if(!strcmp(argument, "--help"))
        return ARGUMENT_HELP;
    size_t argumentLength = strlen(argument);
    if(argument[0] == '-')
        return handleOption(argument + 1, argumentLength - 1);
    return handleInput(argument, argumentLength);
}

static inline STATE checkState() {
    if(!*outputPath.string)
        return STATE_OUTPUT_UNDEFINED;
    return STATE_VALID;
}

static void outputFormatted(const char *const name, char *const buffer, FILE *const outFile) {
    const char *inNewLine = strchr(buffer, '\r') ? "\r\n" : "\n";
    const size_t inNewLineLength = strlen(inNewLine);
    fprintf(outFile, "#define %s", name);
    char *line = buffer, *lineEnd;
    while((lineEnd = strstr(line, inNewLine))) {
        *lineEnd = 0;
        fprintf(outFile, " \\\n\"%s\\n\"", line);
        line = lineEnd + inNewLineLength;
    }
    fprintf(outFile, " \\\n\"%s\"\n", line);
}

int main(const int argc, const char *const argv[]) {
    for(int argI = 1; argI < argc; argI++) {
        ARGUMENT argument = handleArgument(argv[argI]);
        switch(argument) {
            case ARGUMENT_VALID:
                continue;
            case ARGUMENT_HELP:
                printf("\n"
                    "Usage: [-O<output>] (<inputs>)\n"
                    "Outputs the contents of several Files to one Source-File as Preprocessor-Macros.\n"
                    "The string-constants are named like the Files they were taken from.\n"
                    "(Order of the arguments may be ignored)\n\n"
                    "output: Path to the File to output to\n\n"
                    "inputs: List of Paths to Files to use\n"
                    "\tPaths are relative to the current Directory\n"
                    "\tThe current Directory can persistently be changed with \"-D<dir>\"\n"
                );
                return 0;
            default:
                ERR("Invalid Argument at position %u (%s): %s\n", argI, argv[argI], ERRORS_ARGUMENT[argument - 1]);
                return -1;
        }
    }
    STATE state = checkState();
    if(state) {
        ERR("Invalid State: %s\n", ERRORS_STATE[state - 1]);
        return -1;
    }
    FILE *outFile = fopen(outputPath.string, "w");
    if(!outFile) {
        ERR("Output-File (%s) couldn't be opened\n", outputPath.string);
        return -1;
    }
    for(size_t i = 0; i < inputCount; i++) {
        FILE *inFile = fopen(inputPaths[i].string, "rb");
        if(!inFile) {
            ERR("Input-File (%s) couldn't be opened\n", inputPaths[i].string);
            return -1;
        }
        fseek(inFile, 0, SEEK_END);
        long length = ftell(inFile);
        rewind(inFile);
        char *buffer = malloc(length + 1);
        fread(buffer, 1, length, inFile);
        buffer[length] = 0;
        char *filename = strrchr(inputPaths[i].string, '/') + 1;
        toScreamingSnakeCase(filename, inputPaths[i].length - (filename - inputPaths[i].string) - 1);
        outputFormatted(filename, buffer, outFile);
        free(buffer);
        fclose(inFile);
    }
    fclose(outFile);
    free(inputPaths);
}
