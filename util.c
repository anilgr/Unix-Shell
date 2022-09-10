#include "util.h"
#include <stdio.h>
// utility method to inspect cmd struct.
void printCommand(Command *cmd)
{
    printf("\n--- Command start ---\n");
    printf("\n    --- args start ---\n\n");

    for (int i = 0; i < cmd->argsCount; i++)
    {
        printf("    %d. %s\n", i, cmd->args[i]);
    }

    printf("\n    --- args end ---\n");

    printf("\n   argsCount: %d", cmd->argsCount);
    printf("\n   operator: %d", cmd->operator);
    printf("\n   fileName: %s", cmd->fileName);

    printf("\n\n--- Command end ---\n");
}