#include "../minishell.h"


char ****ft_handle_command(char *command)
{
    int     semicolon;
    int     pipes;
    int     spaces;
    char    ****result;
    char    **split_semicolon;
    char    **split_pipes;
    char    **split_spaces;
    semicolon = -1;
    pipes = -1;
    spaces = -1;

    split_semicolon = ft_split(command, ';');
    while (split_semicolon[++semicolon]) {
        DEBUG == 0?:printf("SC[%d]: %s\n",semicolon,split_semicolon[semicolon]);
    }
    return(result);

}

int main () {
    char *command = "ls -la|cd ..;clear;ls -la";


    
    return (0);
}