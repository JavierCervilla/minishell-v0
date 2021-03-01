/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 02:56:54 by dgomez            #+#    #+#             */
/*   Updated: 2021/02/18 10:51:14 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
** FIXME: arreglar gnl, tiene leaks en ft_strdup cn caena vacía.
*/

void  ft_prompt(t_shell *ms)
{
	char *aux;
	ms->pwd = getcwd(NULL, 0);
 	write(1, ms->pwd, ft_strlen(ms->pwd));
	write(1, "\n->", 3);
}

void exitHandler(int signalInt) {
	write(1, "\nExit with SignalInt[", ft_strlen("\nExit with SignalInt["));
	ft_putnbr_fd(signalInt, 1);
	write(1, "]\n", 2);
	write(1, "See you Soon ;-)\n", ft_strlen("See you Soon ;-)\n"));
	keepRunning = 0;
	exit(0);
}

 int main(int argc, char *argv[], char *envp[])
{
	t_shell ms;
	int		semicolon;
	int 	pipes;
	int		status;
	int		cNum;
	int		i = -1;

	char	*arg_ls[]={"/bin/ls","-a", NULL};
	char	**auxArgs;
	char	*auxPath;


	
	ft_bzero(&ms, sizeof(ms));
	/** SIGNAL CHECK */
	signal(SIGINT, exitHandler);
	while (keepRunning)
	{
		/** PROMPT */
		ft_prompt(&ms);
		/** READ */	
		ms.isRead = get_next_line(0, &ms.line);
		/** START PARSING LINE*/
		if (ms.isRead == 1 && ft_strlen(ms.line) > 0)
		{
			/** EXIT WORD TO EXIT*/
			if (ft_strcmp(ms.line, "exit"))
			{
				exit(0);
			}

			ft_parse_command(&ms);
			ft_count_alloc_cmds(&ms);
			cNum = -1;
			semicolon = -1;
			while (ms.commandList[++semicolon])
			{
				pipes = -1;
				while (ms.commandList[semicolon][++pipes])
				{
					/** CMD HANDLER */
					auxArgs = ft_split(ms.commandList[semicolon][pipes],  ' ');
					ms.processList[++cNum].cmd.args = auxArgs;
					ms.processList[cNum].processPid = fork();
					if (ms.processList[cNum].processPid == -1)
					{
						DEBUG == 0?:printf("Error al crear el proceso hijo");
					}
					if (ms.processList[cNum].processPid) {
						DEBUG == 0?:printf("__________PROCESO__PADRE__________\n");
						DEBUG == 0?:printf("PIPES[%d][%d]:%s\n\n",semicolon, pipes,ms.commandList[semicolon][pipes]);
						DEBUG == 0?:printf("PID:%d\n	comando: %s\n\n",  ms.processList[cNum].processPid, ms.commandList[semicolon][pipes]);
						waitpid(-1, &status, 0);
						DEBUG == 0?:printf("STAT:%d\n", status); 
					} else {
						/** 
						* PROCESO HIJO:
						*  Aqui el proceso hijo ya cuenta con un comando, nose si sería necesario
						*  tener clara la salida del redireccionamiento, o tratarlo despues
						*  en el padre y que la salida de la ejecucion siempre sea igual
						*  pero active flags para ser tratado por el padre.
						*/

						DEBUG == 0?:printf("	________PROCESO__HIJO_____________\n");
						DEBUG == 0?:printf("	Nº: %d\n	CMD: %s\n",cNum, ms.commandList[semicolon][pipes]);
 */
						ms.processList[cNum].cmd.program_path = ft_get_program_path(auxArgs[0],envp);
						DEBUG == 0?:printf("P[%d]:%s\n",cNum,ms.processList[cNum].cmd.program_path); */
						ms.processList[cNum].cmd.exec_route = ft_strjoin(ms.processList[cNum].cmd.program_path, "/");
						auxPath = ft_strjoin(ms.processList[cNum].cmd.exec_route,ms.processList[cNum].cmd.args[0]);
						free(ms.processList[cNum].cmd.exec_route);
						ms.processList[cNum].cmd.exec_route = auxPath;
						free(ms.processList[cNum].cmd.args[0]);
						ms.processList[cNum].cmd.args[0] = auxPath;

						ms.processList[cNum].cmd.args[0] = ms.processList[cNum].cmd.exec_route;
						DEBUG == 0?:printf("P[%d]:%s\n",cNum,ms.processList[cNum].cmd.program_path);
						if (execve(ms.processList[cNum].cmd.exec_route,ms.processList[cNum].cmd.args,envp)  == -1)
							printf("error\n");
					}
				}
			}
    	}
			
			
		/** OUTPUT */
		
		/** Liberar memoria */
		ms.isRead = 0;
		free(ms.pwd);
		free(ms.line);
	}
	
	return (0);
}

