#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80 /* The maximum length command */
#define MAX_ARG_SIZE 10

typedef char *string;

int parseCommand(char *command, string args[]);

int main(void)
{
    string args[MAX_LINE / 2 + 1]; /* command line arguments */
    int should_run = 1;           /* flag to determine when to exit program */

    printf("osh>");
    fflush(stdout);
    /**
     * After reading user input, the steps are:
     * (1) fork a child process using fork()
     * (2) the child process will invoke execvp()
     * (3) parent will invoke wait() unless command included & */

    // get user input
    char *command = malloc(MAX_LINE * sizeof(char));

    scanf(" %[^\n]", command);

    parseCommand(command, args);

    return 0;
}

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

