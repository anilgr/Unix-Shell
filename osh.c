#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "osh.h"
#include "parser.h"
#include "command.h"

int main(void)
{
    //string args[MAX_LINE / 2 + 1]; /* command line arguments */
    int should_run = 1;/* flag to determine when to exit program */
    /**
     * After reading user input, the steps are:
     * (1) fork a child process using fork()
     * (2) the child process will invoke execvp()
     * (3) parent will invoke wait() unless command included & */

    // get user input
    char *inputStr = malloc(MAX_LINE * sizeof(char));
    char *previnputStr = malloc(MAX_LINE * sizeof(char));
    Command* cmd = malloc(sizeof(Command));

    while (should_run)
    {
        // show prompt
        printf("osh>");
        fflush(stdout);

        // read input
        scanf(" %[^\n]", inputStr);

        // parse user input
        parseCommand(inputStr, cmd);

        // check if the command is history command and run prev command if yes.
        if (strcmp(cmd->args[0], "!!") == 0) {
            strcpy(inputStr, previnputStr);
            parseCommand(inputStr, cmd);
        } else {
            strcpy(previnputStr, inputStr);
        }

        pid_t pid;
        pid = fork();// create a new child process.

        if (pid == 0)
        {
            execvp(cmd->args[0], cmd->args); // run the command in child process.
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

    free(inputStr);
    free(previnputStr);
    free(cmd);


    return 0;
}
