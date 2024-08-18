#include "/nfs/homes/asabir/Desktop/minishell/minishell.h"

int cmdType(t_params *par)
{
    if(ft_strcmp(par->cmd[0], "echo") == 0)
        return(1);
    else if(ft_strcmp(par->cmd[0], "cd") == 0)
        return(2);
    else if(ft_strcmp(par->cmd[0], "pwd") == 0)
        return(3);
    else if(ft_strcmp(par->cmd[0], "unset") == 0)
        return(4);
    else if(ft_strcmp(par->cmd[0], "export") == 0)
        return(5);
    else if(ft_strcmp(par->cmd[0], "env") == 0)
        return(6);
    else if(ft_strcmp(par->cmd[0], "exit") == 0)
        return(7);
    else
        return(0);
}

void redirect_cmd(t_params *par, int type, int outfile)
{
    if(type == 1)
        ft_echo(par, outfile);
    else if(type == 2)
        ft_cd(par, outfile);
    else if(type == 3)
        ft_pwd(outfile);
    else if(type == 4)
        ft_unset(par);
    else if(type == 5)
        ft_export(par, outfile);
    else if(type == 6)
        ft_env(outfile);
    else if(type == 7)
        ft_exit();
    return;
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
