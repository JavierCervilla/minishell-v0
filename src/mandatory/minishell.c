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
		if (ms.isRead == 1 && ft_strlen(ms.line) > 0)
		{
			if (ft_strcmp(ms.line, "exit"))
			{
				/** Limpiar memoria */
				exit(0);
			}
			if (ft_check_if_quotes(ms.line)){
        		ms.commandList = ft_command_with_quotes(ms.line);
				printf("LLEGO: %s\n", ms.commandList[0][0]);
				printf("LLEGO\n");
    		} else {
        		ms.commandList = ft_command_without_quotes(ms.line);
				printf("LLEGO: %s\n", ms.commandList[0][0]);
       		}
    	}
		semicolon = 0;
		while (ms.commandList[semicolon])
			semicolon++;
		DEBUG == 0?:printf("semicolon: %d\n", semicolon);
		ms.commandsNum = semicolon;
		semicolon = -1;
		while (ms.commandList[++semicolon])
		{
			pipes = -1;
			while (ms.commandList[semicolon][++pipes])
			{
				//DEBUG == 0?:printf("PIPES[%d][%d]:%s\n",semicolon, pipes,ms.commandList[semicolon][pipes]);
				/** CMD HANDLER */
				ms.commandsNum++;
			}
		}
		if (!(ms.processList = (t_process *)malloc(sizeof(t_process) * ms.commandsNum + 1)))
		{
			/** Limpiar memoria */
			exit(0);
		}
		cNum = -1;
		semicolon = -1;
		while (ms.commandList[++semicolon])
		{
			pipes = -1;
			while (ms.commandList[semicolon][++pipes])
			{
				DEBUG == 0?:printf("PIPES[%d][%d]:%s\n",semicolon, pipes,ms.commandList[semicolon][pipes]);

				/** CMD HANDLER */
				auxArgs = ft_split(ms.commandList[semicolon][pipes],  ' ');
				ms.processList[++cNum].cmd.args = auxArgs;
				/* ms.processList[cNum].cmd.program_path = ft_strdup(ft_get_program_path(ms.processList[cNum].cmd.args[0],envp));
				ms.processList[cNum].cmd.exec_route = ft_strjoin(ms.processList[cNum].cmd.program_path, ms.processList[cNum].cmd.args[0]);
				free(ms.processList[cNum].cmd.args[0]);
				ms.processList[cNum].cmd.args[0] = ms.processList[cNum].cmd.exec_route;
				i = -1;
				while (ms.processList[cNum].cmd.args[++i])
					DEBUG == 0?:printf("ARG[%d]:%s\n",i, ms.processList[cNum].cmd.args[i]);
				if (execve(ms.processList[cNum].cmd.args[0],ms.processList[cNum].cmd.args,envp)  == -1)
						printf("	error"); */
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

