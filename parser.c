#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "osh.h"
#include "command.h"

// parse args into given array from the given command.
int parseCommand(char *commandStr, Command* cmd)
{
    int argsIndex = 0;

    char** args = cmd->args;

    args[argsIndex] = malloc(MAX_ARG_SIZE * sizeof(char));
    int k = 0;
    for (int i = 0; i < strlen(commandStr); i++)
    {
        char c = commandStr[i];
        if (c != ' ' && c != '\t')
        {
            args[argsIndex][k] = c;
            k++;
        }
        else
        {
            args[argsIndex][k] = '\0';
            argsIndex++;
            k = 0;
            args[argsIndex] = malloc(MAX_ARG_SIZE * sizeof(char));
        }

    }
    int argsCount = argsIndex + 1;
    
    // for (int j = 0; j < argsCount; j++)
    // {
    //     printf("\n%s\n", args[j]);
    // }

    for (int j = argsCount; j < MAX_LINE / 2 + 1; j++)
    {
        args[j] = NULL;
    }

    return argsCount;
}