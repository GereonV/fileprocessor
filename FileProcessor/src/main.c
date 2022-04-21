#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PATH_LENGTH 256
typedef char PATH[PATH_LENGTH];

long getFileSize(FILE *const file) {
    long position, length;
    position = ftell(file);
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, position, SEEK_SET);
    return length;
}

void convertToConstant(const char *const filename, char *const constant) {
    const char *s = strrchr(filename, '/') + 1;
    size_t i, len = strlen(s);
    for(i = 0; i < len; i++)
        constant[i] = s[i] + ('A' - 'a') * (s[i] >= 'a' && s [i] <= 'z') + ('_' - '.') * (s[i] == '.');
    constant[len] = 0;
}

void outputString(const char *const constant, const char *const s, const char *const newLine, FILE *out, const char *const mode) {
    size_t newLineLen = strlen(newLine);
    fprintf(out, "static const char *%s = \"", constant);
    const char *line = s, *lineEnd;
    while(lineEnd = strstr(line, newLine)) {
        for(const char *c = line; c != lineEnd; c++)
            fputc(*c, out);
        fprintf(out, "\\n\"%s\"", mode);
        line = lineEnd + newLineLen;
    }
    fprintf(out, "%s\";%s", line, mode, mode);
}

int main(const int argc, const char *const argv[]) {
    unsigned int inputCount = 0;
    PATH output = "", *inputs = malloc((argc - 2) * sizeof(PATH)), dir = ".";
    char mode[3] = "";
    size_t dirLen = strlen(dir);
    for(int i = 1; i < argc; i++) {
        const char *s = argv[i];
        const size_t sLen = strlen(s);
        if(s[0] == '-') {
            if(sLen == 1 || sLen - 2 >= PATH_LENGTH) {
                fprintf(stderr, "invalid option length at position %d: '%s'\n", i, s);
                return -1;
            }
            switch(s[1]) {
                case 'O':
                    strcpy(output, s + 2);
                    break;
                case 'M':
                    if(!strcmp(s + 2, "LF"))
                        strcpy(mode, "\n");
                    else if(!strcmp(s + 2, "CRLF"))
                        strcpy(mode, "\r\n");
                    else {
                        fprintf(stderr, "invalid mode at position %d: '%s'\n", i, s);
                        return -1;
                    }
                    break;
                case 'D':
                    strcpy(dir, s + 2);
                    dirLen = sLen - 2;
                    break;
                default:
                    fprintf(stderr, "invalid option at position %d: '%c'\n", i, s[1]);
                    return -1;
            }
        } else {
            if(dirLen + 1 + sLen >= PATH_LENGTH) {
                fprintf(stderr, "too long filename: '%s/%s'\n", dir, s);
                return -1;
            }
            char *ptr = inputs[inputCount++];
            strcpy(ptr, dir);
            ptr[dirLen] = '/';
            strcpy(ptr + dirLen + 1, s);
        }
    }

    if(!output[0]) {
        fprintf(stderr, "no mode provided\n");
        return -1;
    }
    if(!mode[0]) {
        fprintf(stderr, "no mode provided\n");
        return -1;
    }

    FILE *out, *in;
    if(!(out = fopen(output, "wb"))) {
        fprintf(stderr, "couldn't open output: '%s'\n", output);
        return -1;
    }
    PATH constant;
    for(unsigned int i = 0; i < inputCount; i++) {
        if(!(in = fopen(inputs[i], "rb"))) {
            fprintf(stderr, "couldn't open input: '%s'\n", inputs[i]);
            return -1;
        }
        long length = getFileSize(in);
        char *s = malloc(sizeof(char) * (length + 1));
        fread(s, sizeof(char), length, in);
        s[length] = 0;
        convertToConstant(inputs[i], constant);
        outputString(constant, s, strchr(s, '\r') ? "\r\n" : "\n", out, mode);
        free(s);
        fclose(in);
    }
    fclose(out);
    free(inputs);
}
