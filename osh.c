#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "osh.h"
#include "parser.h"
#include "command.h"
#include "util.h"

int main(void)
{
    // string args[MAX_LINE / 2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    /**
     * After reading user input, the steps are:
     * (1) fork a child process using fork()
     * (2) the child process will invoke execvp()
     * (3) parent will invoke wait() unless command included & */

    // get user input
    char *inputStr = malloc(MAX_LINE * sizeof(char));
    char *previnputStr = malloc(MAX_LINE * sizeof(char));
    Command *cmd;

    while (should_run)
    {
        // show prompt
        printf("\nosh>");
        fflush(stdout);

        inputStr = malloc(MAX_LINE * sizeof(char));
        previnputStr = malloc(MAX_LINE * sizeof(char));

        // read input
        scanf(" %[^\n]", inputStr);

        // allocate memory
        cmd = malloc(sizeof(Command));

        // parse user input
        parseCommand(inputStr, cmd);

        // check if the command is history command and run prev command if yes.
        if (strcmp(cmd->args[0], "!!") == 0)
        {
            strcpy(inputStr, previnputStr);
            parseCommand(inputStr, cmd);
        }
        else
        {
            strcpy(previnputStr, inputStr);
        }

        pid_t pid;
        pid = fork(); // create a new child process.

        int stdout_file = dup(stdout->_file);

        if (pid == 0)
        {

            printCommand(cmd);

            if (cmd->operator== OUTPUT_REDIRECTION)
            {
                FILE *fd = fopen(cmd->fileName, "w+");
                dup2(fd->_file, stdout->_file);
            }

            execvp(cmd->args[0], cmd->args);
        }
        else if (pid > 0)
        {
            wait(NULL); // waits for the child process to complete
            cmd->operator = NO_REDIRECTION;
            dup2(stdout->_file, stdout_file);
        }
        else
        {
            // error creating the child process.
            printf("\n%s\n", "Failed to create child process.");
            fprintf(stderr, "Fork failed.");
            return 1;
        }

        free(cmd);
        free(inputStr);
        free(previnputStr);

    }


    return 0;
}
