#include "../minishell.h"

int ft_count_alloc_cmds(t_shell *ms) {
    int semicolon;
    int pipes;

    semicolon = -1;
    while (ms->commandList[++semicolon])
    {
        pipes = -1;
        while (ms->commandList[semicolon][++pipes])
        {
            DEBUG == 0?:printf("PIPES[%d][%d]:%s\n",semicolon, pipes,ms->commandList[semicolon][pipes]);
            ms->commandsNum++;
        }
    }
    if (!(ms->processList = (t_process *)malloc(sizeof(t_process) * ms->commandsNum + 1)))
        return (0);
    return (ms->commandsNum++);
}