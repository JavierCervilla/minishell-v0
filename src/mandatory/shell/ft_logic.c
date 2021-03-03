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
            //DEBUG == 0?:printf("PIPES[%d][%d]:%s\n",semicolon, pipes,ms->commandList[semicolon][pipes]);
            ms->commandsNum++;
        }
    }
    if (!(ms->processList = (t_process *)malloc(sizeof(t_process) * ms->commandsNum + 1)))
        return (0);
    return (ms->commandsNum++);
}

int ft_parse_args(t_shell *ms, int cNum, char *envp[], char	**auxArgs)
{
    char	*auxPath;

    ms->processList[cNum].cmd.program_path = ft_get_program_path(auxArgs[0],envp);
    // DEBUG == 0?:printf("P[%d]:%s\n",cNum,ms->processList[cNum].cmd.program_path);
    ms->processList[cNum].cmd.exec_route = ft_strjoin(ms->processList[cNum].cmd.program_path, "/");
    auxPath = ft_strjoin(ms->processList[cNum].cmd.exec_route,ms->processList[cNum].cmd.args[0]);
    free(ms->processList[cNum].cmd.exec_route);
    ms->processList[cNum].cmd.exec_route = auxPath;
    free(ms->processList[cNum].cmd.args[0]);
    ms->processList[cNum].cmd.args[0] = auxPath;
    ms->processList[cNum].cmd.args[0] = ms->processList[cNum].cmd.exec_route;
    // DEBUG == 0?:printf("P[%d]:%s\n",cNum,ms->processList[cNum].cmd.program_path);
    return (1);
}

int ft_execute_loop(t_shell *ms, char *envp[]) {
    int     cNum;
    int     semicolon;
    int     pipes;
	char	**auxArgs;


    cNum = -1;
    semicolon = -1;
    while (ms->commandList[++semicolon])
    {
        pipes = -1;
        while (ms->commandList[semicolon][++pipes])
        {
            /** CMD HANDLER */
            /** Separacion de los argumentos del comando por espacios **/
            auxArgs = ft_split(ms->commandList[semicolon][pipes],  ' ');
            ms->processList[++cNum].cmd.args = auxArgs;
            ms->processList[cNum].processPid = fork();
            if (ms->processList[cNum].processPid == -1)
            {
                // DEBUG == 0?:printf("Error al crear el proceso hijo");
            }
            if (ms->processList[cNum].processPid) {
                // DEBUG == 0?:printf("__________PROCESO__PADRE__________\n");
                // DEBUG == 0?:printf("PIPES[%d][%d]:%s\n\n",semicolon, pipes,ms->commandList[semicolon][pipes]);
                // DEBUG == 0?:printf("PID:%d\n	comando: %s\n\n",  ms->processList[cNum].processPid, ms->commandList[semicolon][pipes]);
                waitpid(-1, &ms->status, 0);
                // DEBUG == 0?:printf("STAT:%d\n", ms->status); 
            } else {
                /** 
                * PROCESO HIJO:
                *  Aqui el proceso hijo ya cuenta con un comando, nose si sería necesario
                *  tener clara la salida del redireccionamiento, o tratarlo despues
                *  en el padre y que la salida de la ejecucion siempre sea igual
                *  pero active flags para ser tratado por el padre.
                */

                // DEBUG == 0?:printf("	________PROCESO__HIJO_____________\n");
                // DEBUG == 0?:printf("	Nº: %d\n	CMD: %s\n",cNum, ms->commandList[semicolon][pipes]);
                /** Aqui ira la comprobacion de que no sea un programa de los nuestros **/
                /** Buscamos el path del programa y concatenamos el path al programa **/
                if (!ft_parse_args(ms, cNum, envp, auxArgs))
                {
                    printf("___ERROR_EN_PROCESO_HIJO___");
                }
                /** Lanzamos la ejecucion del programa **/
                if (execve(ms->processList[cNum].cmd.exec_route,ms->processList[cNum].cmd.args,envp)  == -1)
                {
                    printf("error\n");
                    return (0);
                }
            }
        }
    }
    return (1);
}