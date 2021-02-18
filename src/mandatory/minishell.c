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
			if (!(ms.processList = (t_process *)malloc(sizeof(t_process) * count)))
			{
				/** Limpiar memoria */
				exit(0);
			}
			count = 0;
			while (ms.commandList[count])
			{
				/** COMMAND HANDLER */
				ms.processList[count].processPid = fork();
				if (ms.processList[count].processPid == -1)
				{
					printf("Error al crear el proceso hijo, Numero de comando: %d\n comando: %s\n", count, ms.commandList[count]);
				}
				/** PROCESO PADRE */
				if (ms.processList[count].processPid) {
					printf("__________PROCESO__PADRE__________\n");
					printf("PID:%d\n	comando: %s\n",  ms.processList[count].processPid, ms.commandList[count]);
					waitpid(-1, &status, 0);
					printf("STAT:%d\n", status);
				} else {
					/** PROCESO HIJO*/
					printf("	________PROCESO__HIJO_____________\n");
					printf("	Nº: %d\n	CMD: %s\n",count, ms.commandList[count]);

					printf("LLEGO\n");
					ms.processList[count].cmdList[0].program_path = ft_get_program_path(ms.commandList[count],envp);
					printf("PATH_DIR: %s\n",ms.processList[count].cmdList[0].program_path);
					/** 
					 * Aqui el proceso hijo ya cuenta con un comando, nose si sería necesario
					 * tener clara la salida del redireccionamiento, o tratarlo despues
					 * en el padre y que la salida de la ejecucion siempre sea igual
					 * pero active flags para ser tratado por el padre.
					*/

					if (execve(arg_ls[0],arg_ls,envp)  == -1)
						printf("	error");
					
				}
				count++;
			}
			
			/** OUTPUT */
		}
		/** Liberar memoria */
		ms.isRead = 0;
		free(ms.pwd);
		free(ms.line);
	}
	
	return (0);
}

