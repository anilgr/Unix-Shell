#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "osh.h"
#include "parser.h"

int main(void)
{
    string args[MAX_LINE / 2 + 1]; /* command line arguments */
    int should_run = 1;
    int argsCount; /* flag to determine when to exit program */
    /**
     * After reading user input, the steps are:
     * (1) fork a child process using fork()
     * (2) the child process will invoke execvp()
     * (3) parent will invoke wait() unless command included & */

    // get user input
    char *command = malloc(MAX_LINE * sizeof(char));
    char *prevCommand = malloc(MAX_LINE * sizeof(char));

    while (should_run)
    {
        // show prompt
        printf("osh>");
        fflush(stdout);

        // read input
        scanf(" %[^\n]", command);

        // parse user input
        argsCount = parseCommand(command, args);

        // check if the command is history command and run prev command if yes.
        if (strcmp(args[0], "!!") == 0) {
            strcpy(command, prevCommand);
            argsCount = parseCommand(command, args);
        } else {
            strcpy(prevCommand, command);
        }

        pid_t pid;
        pid = fork();// create a new child process.

        if (pid == 0)
        {
            execvp(args[0], args); // run the command in child process.
        }
        else if (pid > 0)
        {
            wait(NULL); // waits for the child process to complete
        } else {
            // error creating the child process.
            printf("\n%s\n", "Failed to create child process.");
            fprintf(stderr, "Fork failed.");
            return 1;
        }
    }

    return 0;
}
