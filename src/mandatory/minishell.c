/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 02:56:54 by dgomez            #+#    #+#             */
/*   Updated: 2021/01/20 18:26:20 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void ft_prompt()
{
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	write(1, cwd, sizeof(cwd));
	write(1, "\n->", 3);
}

int main(int argc, char *argv[])
{
	char *line;
	int isRead;

	/** PROMPT */

	ft_prompt();
	/** READ */
	isRead = get_next_line(0, &line);
	if (isRead == 1)
	{
		/** COMMAND HANDLER */
		printf("%s\n", line);
	}
	/** OUTPUT */
	printf("output\n");
	return (0);
}