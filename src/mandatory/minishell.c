/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 02:56:54 by dgomez            #+#    #+#             */
/*   Updated: 2021/01/24 14:00:03 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"


void  ft_prompt(t_shell *ms)
{
	ms->pwd = getcwd(NULL, 0);
 	write(1, ms->pwd, ft_strlen(ms->pwd));
	write(1, "\n->", 3);
}

int main(int argc, char *argv[])
{
	t_shell ms;
	char *line;
	int isRead;

	ft_bzero(&ms, sizeof(ms));
	while (!ms.exit)
	{
		/** PROMPT */
		ft_prompt(&ms);
		/** READ */	
		ms.isRead = get_next_line(0, &line);
		/** SIGNAL CHECK */
		
		if (ms.isRead == 1)
		{
			/** COMMAND HANDLER */
			printf("command:%s\n", line);
		}
		/** OUTPUT */
		printf("output\n");
		ms.isRead = 0;
	}
	
	return (0);
}