#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "osh.h"
#include "util.h"
#include "command.h"

// parse args into given array from the given command.
int parseCommand(char *commandStr, Command *cmd)
{
    int argsIndex = 0;

    char **args = cmd->args;

    args[argsIndex] = malloc(MAX_ARG_SIZE * sizeof(char));

    for (int i = 0; i < strlen(commandStr); i++)
    {
        char c = commandStr[i];

        if (c == '>'){
            printf("\n output redirection.\n");

            i++;
            int k = 0;
            for (;i < strlen(commandStr) && k < MAX_FILE_NAME_LENGTH; i++) {
                c = commandStr[i];
                if (c != ' ' )
                {
                    cmd->fileName[k] = c;
                    k++;
                }
            }
            cmd->fileName[k] = '\0';

            cmd->operator = OUTPUT_REDIRECTION;

            printf("Debug: %s", cmd->fileName);

            break;
        }

        if (c == '<'){
            printf("\n output redirection.\n");

            i++;
            int k = 0;
            for (;i < strlen(commandStr) && k < MAX_FILE_NAME_LENGTH; i++) {
                c = commandStr[i];
                if (c != ' ' )
                {
                    cmd->fileName[k] = c;
                    k++;
                }
            }
            cmd->fileName[k] = '\0';

            cmd->operator = INPUT_REDIRECTION;

            printf("Debug: %s", cmd->fileName);

            break;
        }

        int argIndex = -1;
        for (; c != ' ' && i < strlen(commandStr); i++)
        {
            c = commandStr[i];

            printf("\t|%c|", c);


            if (argIndex == -1)
            {
                cmd->args[argsIndex] = malloc(MAX_ARG_SIZE * sizeof(char));
                argIndex = -1;
            }

            argIndex++;
            cmd->args[argsIndex][argIndex] = c;
        }

        if (c == ' ' && argIndex > -1)
        {
            cmd->args[argsIndex][argIndex++] = '\0';
            argsIndex++;
            i--;
        }
    }

    int argsCount = argsIndex + 1;
    cmd->argsCount = argsCount;

    for (int j = argsCount; j < MAX_LINE / 2 + 1; j++)
    {
        args[j] = NULL;
    }

    return argsCount;
}

/**
 *     ls lsdfkl jsldf jlksdf    > output.txt
 *
 *     args argsIndex = 0;
 *     cosume space
 * get chars which are not '\n' or '>'
 *  */