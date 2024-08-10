#include "../minishell.h"

char *find_path(char **env)
{
    int i;

    i = 0;
    while(env[i])
    {
        if(ft_strncmp(env[i], "PATH=", 5)==0)
            return (env[i]+5);
        i++;
    }
    return(NULL);
}

int search_cmd(char *cmd, char **env)
{
    char *path_variable;
    char **paths;
    int i;

    path_variable = find_path(env);
    i = 0;
    if(path_variable == NULL)
        handle_error();
    else
    paths = ft_split(path_variable);
    while(paths[i])
    {
        
    }
    return ();
}

void ft_executable(char **cmd)
{
    int i;
    int id;

    id = fork();
    if(id == -1)
        handle_error();
    if(id == 0)
    {
        
    }
}