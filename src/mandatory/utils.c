/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:00:46 by jcervill          #+#    #+#             */
/*   Updated: 2021/02/17 13:57:29 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char    *ft_getenv(const char *name, char *envp[])
{
	int     k;
	char	*res;
    res = NULL;
	k = -1;
	while(envp[++k])
	{
        //printf("envp[%d] = %s\n", k, envp[k]);	
		if((res = ft_strnstr(envp[k], name, ft_strlen(name))))
			break;
	}
	return(res);
}

int     do_into_dir(char *dir, char *program)
{
    DIR             *dirp;
    struct dirent   *direntp;
	int		found;

	dirp = NULL;
	direntp = NULL;
	found = 0;	
	if(!(dirp = opendir(dir)))
		return(-1);
	while ((direntp = readdir(dirp)) && !found)
		if(ft_strncmp(direntp->d_name, program, ft_strlen(direntp->d_name)) == 0
        && ft_strncmp(program,direntp->d_name, ft_strlen(program)) == 0)
			found = 1;
	if(!dirp)
		closedir(dirp);
    /* printf("found = %d\n", found); */
	return(found);
}


char    *ft_get_program_path(char *programName, char *envp[]) {
    char    **path;
    char    **path_dirs;
    int     i;
    char    *res;

    if (ft_strlen(programName) == 0 || !programName)
        return ft_strdup("");
    path = ft_split(ft_getenv("PATH", envp), '=');
    /* printf("PATH:\n%s\n", path[1]); */
    path_dirs = ft_split(path[1], ':');
    i = -1;
    /* printf("PROGRAM: %s\n",  programName); */
    while (path_dirs[++i] && !res)
    {
        /* printf("dir: %s\n", path_dirs[i]); */
        if (do_into_dir(path_dirs[i], programName) > 0)
        {
            res = ft_strdup(path_dirs[i]);
            /* printf("res: %s\n", res);*/
        }
    }
    return res;
}

/* int     main(int argc, char *argv[],char **envp) {
    printf("PATH_DIR: %s\n",ft_get_program_path("", envp));
    return (0);
} */ 