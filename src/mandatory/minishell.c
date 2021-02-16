/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 02:56:54 by dgomez            #+#    #+#             */
/*   Updated: 2021/02/16 13:50:59 by jcervill         ###   ########.fr       */
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
	int		count;
	int status;

	char *arg_ls[]={"/bin/ls","-a", NULL};


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
			ms.commandList = ft_split(ms.line, ';');
			count = 0;
			while (ms.commandList[count])
				count++;
			printf("count: %d\n", count);
			ms.commandsNum = count;
			if (!(ms.processList = (int *)malloc(sizeof(pid_t) * count)))
			{
				/** Limpiar memoria */
				exit(0);
			}
			count = 0;
			while (ms.commandList[count])
			{
				/** COMMAND HANDLER */
				ms.processList[count] = fork();
				if (ms.processList[count] == -1)
				{
					printf("Error al crear el proceso hijo, Numero de comando: %d\n comando: %s\n", count, ms.commandList[count]);
				}
				/** PROCESO PADRE */
				if (ms.processList[count]) {
					printf("__________PROCESO__PADRE__________\n");
					printf("Soy el proceso padre, PID:%d\n comando: %s\n",  ms.processList[count], ms.commandList[count]);
					waitpid(-1, &status, 0);
				} else {
					/** PROCESO HIJO*/
					printf("__________PROCESO__HIJO_____________\n");
					printf("Soy el proceso hijo, Numero de comando: %d\n comando: %s\n",count,  ms.commandList[count]);
					if (execve(arg_ls[0],arg_ls,envp)  == -1)
						printf("error");
				}
				count++;
			}
			
			/** OUTPUT */
			printf("output\n");
		}
		/** Liberar memoria */
		ms.isRead = 0;
		free(ms.pwd);
		free(ms.line);
	}
	
	return (0);
}