#include "../minishell.h"

void ft_export(t_params *par)
{
    int i;
    int found;

    i = 0;
    found = 0;
    if(par->cmd[1] == NULL)
    {
        while(environ[i])
    } 
    while(environ[i])
    {
        if(ft_strncmp(name, environ[i], ft_strlen(name)) == 0)
        {   
            free(environ[i]);
            environ[i]= fill_and_concat(name, value);
            found = 1;
        }
        i++;
    }
    if(found == 0)
    {

    }
}

void ft_env(t_params *par)
{

}

void ft_exit(t_params *par)
{

}