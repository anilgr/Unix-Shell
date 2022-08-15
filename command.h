#ifndef __COMMAND_HEADER
#define __COMMAND_HEADER
typedef struct {
    char* args [MAX_LINE / 2 + 1];
    int argsCount;
} Command;
#endif
