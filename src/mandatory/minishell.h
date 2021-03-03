/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 01:34:16 by jcervill          #+#    #+#             */
/*   Updated: 2021/02/18 10:48:13 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
/*
**  INCLUDES
*/
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "../../includes/printf/ft_printf.h"
#include <signal.h>
#include <dirent.h>
#ifdef __linux__
#define KEY_ESC 65307
#define KEY_C 99
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_UP 65362
#define KEY_RIGHT 65363
#define KEY_DOWN 65364
#else
#define KEY_ESC 53
#define KEY_C 8
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_P 35
#define KEY_LEFT 123
#define KEY_UP 126
#define KEY_RIGHT 124
#define KEY_DOWN 125
#endif

/*
 ** CONSTANTES
*/

#define TRUE 1
#define FALSE 0
#define DEBUG TRUE


/*
**  STRUCTS
*/


static volatile int keepRunning = 1;


typedef struct s_command
{
    char        *program_path;
    char        *exec_route;
    char        **args;
}              t_command;


typedef struct  s_process
{
    pid_t       processPid;     // Lista de procesos, cada proceso tiene la lista de los padres
    t_command   cmd;     // Lista de commands
}               t_process;


typedef struct	s_hell
{
	char        *pwd;           // Working directory -> ft_prompt
    int         exit;           // Flag activated by signal to exit ctrl-c ctrl-x ctrl-d
    int         isRead;         // Line is read, detected by '\n'
    char        *line;          // Line buffer.
    char        ***commandList;  // Arr de comandos tras split por ';' y '|'
    int         commandsNum;    // numero de comandos
    t_process   *processList;   //  Lista de procesos
    int         status;         // estado, Signal
}				t_shell;


/*
** errors
*/

void ft_handle_error(char *str);

/*
** Read Utils
*/

void    ft_parse_command(t_shell *ms);
int     ft_check_if_quotes(char *command);
char    ***ft_split_clean_command(char *cmd);
char    ***ft_command_without_quotes(char *cmd);
char    ***ft_command_with_quotes(char *cmd);


/*
*   System Utils
*/


char    *ft_getenv(const char *name, char *envp[]);
char    *ft_get_program_path(char *programName, char *envp[]);


/*
** MINISHELL LOGIC
*/
int ft_count_alloc_cmds(t_shell *ms);
int ft_execute_loop(t_shell *ms, char *envp[]);
int ft_parse_args(t_shell *ms, int cNum, char *envp[], char	**auxArgs);

void ft_prompt(t_shell *ms);

#endif
