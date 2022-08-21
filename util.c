#include "util.h"
#include <stdio.h>
// utility method to inspect cmd struct.
void printCommand(Command *cmd)
{
    printf("\n--- Command start ---\n");
    printf("\n    args start ---\n");
    // for (int i = 0; i < cmd->argsCount; i++)
    // {
    //     printf("   %s\n", cmd->args[i]);
    // }

    printf("\n   argsCount: %d", cmd->argsCount);
    printf("\n   operator: %d", cmd->operator);
    printf("\n   fileName: %s", cmd->fileName);

    printf("\n--- Command end ---\n");
}