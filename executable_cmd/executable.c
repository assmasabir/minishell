#include "../minishell.h"

char *find_path()
{
    int i;

    i = 0;
    while(environ[i])
    {
        if(ft_strncmp(environ[i], "PATH=", 5)==0)
            return (environ[i]+5);
        i++;
    }
    printf("i am here\n");
    return(NULL);
}

int is_cmd_present(char **paths, char *cmd, char **path_variable)
{
    int i;

    char *join;
    char *temp;

    i = 0;
    if(ft_strchr(cmd, '/') == 0)
    {
        if(access(cmd, X_OK) == 0)
            *path_variable = cmd;
        else
        {
            // free());
            return(-1);
        }
    }
    else
    {    
        while(paths[i])
        {
            temp = ft_join(paths[i], "/");
            join = ft_join(temp, cmd);
            printf("%s\n", join);
            if(access(join, X_OK) == 0)
            {
                *path_variable = paths[i];
                free(join);
                free(temp);
                // free_matrix(paths);
                return(0);
            }
            free(temp);
            free(join);
            i++;
        }
        free_matrix(paths);
    }
    return(-1);
}

int search_cmd(char *cmd, char **path_variable)
{

    int check;
    char *full_path;
    char **paths;

    full_path = find_path();
    if(full_path == NULL)
    {
        write(1, "r\n", 2);
        return (-1);
    // handle_error(); //! bash: cmd: No such file or directory
    }
    else
    {
        paths = ft_split(full_path, ':');
        printf("full path %s \n", full_path);
        int b;
        b = 0;
        while(paths[b])
        {
            printf("%s\n", paths[b]);
            b++;
        }
        check = is_cmd_present(paths, cmd, path_variable);
        printf("check : %d\n", check);
        printf("path_variable in search cmd %s\n", *path_variable);
        if(check == -1)
        {
            printf("i am here lalala \n");
            perror(NULL); //! Command 'cmd' not found
            return(-1);
        }
        else
            return(0);
    }
    return (-1);
}

void child_process(t_params* par, int infile, int outfile, char *path_variable)
{
    printf("waaak waaaaak1 : ");
    int id;

    id = fork();
    if(id == -1)
    {
        write(1, "error\n", 6);
        // handle_error(); //!free if you have sth to
    }

    if(id == 0)
    {
        if(dup2(infile, STDIN_FILENO) == -1)
        {
            perror(NULL);
            exit(-1);
        }
        if(dup2(outfile, STDOUT_FILENO) == -1)
        {
            perror(NULL);
            exit(-1);
        }
        execve(path_variable, par->cmd, environ);
    }
}