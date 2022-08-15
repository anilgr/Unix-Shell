#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "osh.h"
//parse args into given array from the given command.
int parseCommand(char *command, string args[]) {
    int argsIndex = 0;

    printf("%s", command);
    args[argsIndex] = malloc(MAX_ARG_SIZE * sizeof(char));
    int k = 0;
    for (int i = 0; i < strlen(command); i++) {
        char c = command[i];
        if (c != ' ' && c != '\t' ) {
            args[argsIndex][k] = c;
            k++;
        } else { 
            args[argsIndex][k] = '\0';
            argsIndex++;
            k = 0;
            args[argsIndex] = malloc(MAX_ARG_SIZE * sizeof(char));
        }
    }
    int argsCount = argsIndex + 1;
    for (int j = 0; j < argsCount; j++) {
        printf("\n%s\n", args[j]);
    }

    return argsCount;
}