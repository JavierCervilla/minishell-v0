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
	int		cNum;
	int		i = -1;

	char	*arg_ls[]={"/bin/ls","-a", NULL};



	
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
			ft_execute_loop(&ms, envp);
    	}
			
			
		/** OUTPUT */
		
		/** Liberar memoria */
		ms.isRead = 0;
		free(ms.pwd);
		free(ms.line);
	}
	
	return (0);
}

