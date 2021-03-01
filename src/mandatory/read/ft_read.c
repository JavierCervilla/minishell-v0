#include "../minishell.h"


int    ft_check_if_quotes(char *command) {
    int i;

    i = -1;
    while (command[++i])
        if (command[i] == '"')
            return TRUE;
    return FALSE;
}



char ***ft_split_clean_command(char *cmd) {
    char    **split_semicolon;
    char    ***split_pipes;
    int     i;
    int     j;
    
    i = -1;
    split_semicolon = ft_split(cmd, ';');
    while (split_semicolon[++i]){
        DEBUG == 0?:printf("semicolon(;)[%d]: %s\n", i, split_semicolon[i]);
    }
    if (!(split_pipes = (char ***)malloc(sizeof(char **) * i + 1)))
    {
        i = -1;
        while (split_semicolon[++i]){
            free(split_semicolon[i]);
        }
        free(split_semicolon);
        return (NULL);
    }
    i = -1;
    while (split_semicolon[++i]){
        split_pipes[i] = ft_split(split_semicolon[i], '|');
        j = -1;
        while (split_pipes[i][++j]){
            DEBUG == 0?:printf("pipes(|)[%d][%d]: %s\n", i, j, split_pipes[i][j]);
        }
    }
    return (split_pipes);

}

char    ***ft_command_without_quotes(char  *cmd) {
    DEBUG == 0?:printf("THERE IS NOT QUOTES\n");
    return (ft_split_clean_command(cmd));
}
char    ***ft_command_with_quotes(char  *cmd) {

    DEBUG == 0?:printf("THERE IS QUOTES\n");
    /* 
    **  #TODO:Here we have to parse with quotes
    **
    */
    return (ft_split_clean_command(cmd));
}


void ft_parse_command(t_shell *ms) {
    if (ft_check_if_quotes(ms->line))
    {
        /** COMANDO CON COMAS*/
        ms->commandList = ft_command_with_quotes(ms->line);
        DEBUG == 0?:printf("CMD_W_Q: %s\n", ms->commandList[0][0]);

    }
    else
    {
        /** COMANDO SIN COMAS*/
        ms->commandList = ft_command_without_quotes(ms->line);
        DEBUG == 0?:printf("CMD_WO_Q: %s\n", ms->commandList[0][0]);
    }
}

/* int main () {
    char    *command = "echo ANTES: ; ls -la ; touch test; echo DESPUES: ;ls -la;rm test; echo DELETE: | ls -la";
    char    ***cmd_splited;
    int i,j;

    i = -1;
    j = -1;
    if (ft_check_if_quotes(command)){
        ft_command_with_quotes(command);
    } else {
        cmd_splited = ft_split_clean_command(command);
        while (cmd_splited[++i]){
            j = -1;
            while(cmd_splited[i][++j]){
                DEBUG == 0?:printf("CMD[%d][%d]: %s\n", i, j, cmd_splited[i][j]);
            }
        }
    }
    return (0);
} */
