#include "../minishell.h"


int    ft_check_if_quotes(char *command) {
    int i;

    i = -1;
    while (command[++i])
        if (command[i] == '"')
            return TRUE;
    return FALSE;
}



int main () {
    char *command = "ls -la|echo \"hola mundo;\";clear;ls -la";
    if (ft_check_if_quotes(command)){
        printf("THERE IS QUOTES\n");
    } else {
        printf("THERE IS NOT QUOTES\n");
    }
    return (0);
}