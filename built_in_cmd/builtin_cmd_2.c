#include "../minishell.h"

// handle printing an envirment variable
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

// void ft_env(t_params *par)
// {

// }

// void ft_pwd(t_params *par)
// {

// }

// void ft_unset(t_params *par)
// {

// }
