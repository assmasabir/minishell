#include "minishell.h"

void redirect_cmd(t_params *par)
{
    if(!par->cmd)
        handle_this_case();
    else if(ft_strcmp(par->cmd[0], "echo") == 0)
        ft_echo(par);
    else if(ft_strcmp(par->cmd[0], "cd") == 0)
        ft_cd(par);
    else if(ft_strcmp(par->cmd[0], "pwd") == 0)
        ft_pwd(par);
    else if(ft_strcmp(par->cmd[0], "unset") == 0)
        ft_unset(par);
    else if(ft_strcmp(par->cmd[0], "export") == 0)
        ft_export(par);
    else if(ft_strcmp(par->cmd[0], "env") == 0)
        ft_env(par);
    else if(ft_strcmp(par->cmd[0], "exit") == 0)
        ft_exit(par);
    else
        ft_executable(par->cmd);
}

void allocate_array(t_params *par, int nb_pipes)
{
    int i;

    i = 0;
    par->fd = malloc(sizeof(int*)*(nb_pipes+1));
    while(i <= nb_pipes)
    {
        par->fd[i]= malloc(sizeof(int)*2);
        i++;
    }
}


void manage_cmds(t_params *par)
{
    int *fd;
    int i;
    int nb_pipes;

    i = 0;
    par->fd_pos = 0;
    par->nb_nodes = list_size(par);
    nb_pipes = par->nb_nodes - 1;
    allocate_array(par, nb_pipes);
    while(i<= nb_pipes)
    {
        if(pipe(fd[i] !=- 1))
            exit(EXIT_FAILURE);
        i++;
    }
    i = 0;
    while(i <= nb_pipes)
    {
        redirect_cmd(par);
        i++;
    }
}
