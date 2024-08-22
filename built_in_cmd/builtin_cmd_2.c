#include "../minishell.h"

char *return_value_env_if_exists(char *key)
{
    int i;
    int j;
    int z;
    char *value;
    char *key_env;

    value = NULL;
    i = 0;
    j = 0;
    z = 0;
    while(environ[i])
    {
        key_env = return_key(environ[i]);
        if(ft_strcmp(key_env, key) == 0)
        {
            value = malloc(sizeof(char)*ft_strlen(environ[i]));
            while(environ[i][j] && environ[i][j] != '=')
                j++;
            j++;
            while(environ[i][j])
                value[z++]=environ[i][j++];
            value[z] = '\0';
            free(key_env);
            return(value);
        }
        free(key_env);
        i++;
    }
    return(value);
}

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
    //! else if()
    //! {
        
    // !}
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

void ft_env(int fd)
{
    int i;

    i = 0;
    while(environ[i])
    {
        ft_putstr(environ[i], fd);
        if(environ[i+1])
            write(fd, "\n", 1);
        i++;
    }
}

void ft_pwd(int fd)
{
    char *value_pwd;

    if(environ == NULL)
    {
        //!PWD IS UNSET
    }
    value_pwd = return_value_env_if_exists("PWD");
    if(value_pwd == NULL)
    {
        //!PWD IS UNSET
    }
    else
        ft_putstr(value_pwd, fd);
    free(value_pwd);
}

void ft_unset(t_params *par)
{
    int i;
    int check;
    char *key_env;
    int j;
    int z;

    z = 1;
    while(par->cmd[z])
    {   
        i = 0;
        j = 0;
        check = 0;
        while(environ[i])
        {
            key_env = return_key(environ[i]);
            if(ft_strcmp(key_env, par->cmd[z]) == 0)
            {
                check = 1;
                free(key_env);
                break;
            }
            free(key_env);
            i++;
        }
        if(check == 1)
        {
            while(environ[j])
            {
                if(i == j)
                {
                    while(environ[j + 1])
                    {
                        environ[j]= environ[j + 1];
                        j++;
                    }
                    environ[j] = NULL;
                    break;
                }
                j++;
            }
        }
        z++;
    }
}

void ft_exit()
{

}
