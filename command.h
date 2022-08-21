
#include "osh.h"
#ifndef __COMMAND_HEADER
#define __COMMAND_HEADER

#define MAX_FILE_NAME_LENGTH 10
typedef enum {
    NO_REDIRECTION,
    INPUT_REDIRECTION,
    OUTPUT_REDIRECTION
} Operator;

typedef struct {
    char* args [MAX_LINE / 2 + 1];
    int argsCount;
    Operator operator;
    char fileName[MAX_FILE_NAME_LENGTH];
} Command;
#endif
