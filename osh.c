#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include "osh.h"
#include "parser.h"

int main(void)
{
    string args[MAX_LINE / 2 + 1]; /* command line arguments */
    int should_run = 1; 
    int argsCount;          /* flag to determine when to exit program */

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

    //parse user input
    argsCount = parseCommand(command, args);

    return 0;
}



