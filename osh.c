#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "osh.h"
#include "parser.h"
#include "command.h"
#include "util.h"

void runCmd(Command *);

int main(void)
{
    int should_run = 1; /* flag to determine when to exit program */

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
        // allocate memory to Command struct
        cmd = malloc(sizeof(Command));

        // read input
        scanf(" %[^\n]", inputStr);

        // parse user input
        parseCommand(inputStr, cmd);

        // check if the command is history command and run prev command if yes.
        if (strcmp(cmd->args[0], "!!") == 0)
        {
            strcpy(inputStr, previnputStr);
            parseCommand(inputStr, cmd);
        }
        else
            strcpy(previnputStr, inputStr);

        runCmd(cmd);

        free(cmd);
        free(inputStr);
        free(previnputStr);
    }

    return 0;
}

// to be run in separate process since
void runCmd(Command *cmd)
{

    pid_t pid;
    pid = fork(); // create a new child process.

    int stdout_file = dup(stdout->_file);
    int stdin_file = dup(stdin->_file);

    printf("stdout fileno: %d\n", stdout->_file);

    if (pid == 0)
    {
        printCommand(cmd);
        if (cmd->operator== OUTPUT_REDIRECTION)
        {
            FILE *fd = fopen(cmd->fileName, "w+");
            dup2(fd->_file, stdout->_file);
            printf("stdout redirected fileno: %d\n", stdout->_file);
            printf("fd fileno: %d\n", fd->_file);
            fclose(fd);
        }

        if (cmd->operator== INPUT_REDIRECTION)
        {
            FILE *fd = fopen(cmd->fileName, "r+");
            dup2(fd->_file, stdin->_file);
            printf("stdout redirected fileno: %d\n", stdout->_file);
            printf("fd fileno: %d\n", fd->_file);
            fclose(fd);
        }

        execvp(cmd->args[0], cmd->args);
    }
    else if (pid > 0)
    {
        wait(NULL); // waits for the child process to complete
        cmd->operator= NO_REDIRECTION;
        dup2(stdout->_file, stdout_file);
        dup2(stdin->_file, stdin_file);
    }
    else
    {
        // error creating the child process.
        printf("\n%s\n", "Failed to create child process.");
        fprintf(stderr, "Fork failed.");
        exit(1);
    }
}
