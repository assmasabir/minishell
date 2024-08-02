#include "../minishell.h"



void ft_echo(t_params *par, int fd)
{
    int i;

    i = 1;
    if(par->cmd[1] == NULL)
        write(fd,"\n",1);
    else if(ft_strcmp(par->cmd[1], "-n") == 0)
    {
        if(par->cmd[2] != NULL)
        {
            i++;
            while(par->cmd[i])
            {
                ft_putstr(par->cmd[i], fd);
                if(par->cmd[i+1])
                    write(fd, " ", 1);
                i++;
            }
        }
    }
    else
    {
        while(par->cmd[i])
        {
            ft_putstr(par->cmd[i], fd);
            if(par->cmd[i+1])
                write(fd, " ", 1);
            i++;
        }
        write(fd, "\n", 1);
    }
}

void ft_cd(t_params *par, int output)
{
    char *old_env;
    char *current_env;

    if(par->cmd[1] == NULL || ft_strcmp(par->cmd[1], ".") == 0)
        free_and_exit_succes();
    else if(ft_strcmp(par->cmd[1], "-") == 0)
    {
        old_env = getenv("OLDPWD");
        current_env = getenv("PWD");
        write(1, "\n", 1);
        if(chdir(old_env) == -1)
        {
            //!perro_ end exit failure(ex : if OLDPWD is unset)
            //!exit(1);
        }
        else
        {
            ft_putstr(old_env, output);
            ft_setenv("OLDPWD", current_env);
            ft_setenv("PWD", old_env);
        }
    }
    else if(ft_strcmp(par->cmd[1], ".." == 0))
    {

    }
    else if(ft_strcmp(par->cmd[1], "~" == 0))
    {

    }
}

// void ft_pwd(t_params *par)
// {

// }

// void ft_unset(t_params *par)
// {

// }
