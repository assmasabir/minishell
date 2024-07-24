#include <../../minishell.h>

int count_variables(t_params *par)
{
    int i;
    int nb;

    i = 1;
    nb = 0;
    while(par->cmd[i])
    {
        if(check_if_add_change_append(par->cmd[i]) == 0)
            nb++;
        i++;
    }
    return(nb);
}

int size_env(char **env)
{
    int i;

    i = 0;
    while(env[i])
    {
        i++;
    }
    return(i);
}

char *return_key(char* str)
{
    int i;
    char *key;

    i = 0;
    key = NULL;
    while(str[i] && str[i] != '=')
    {
        key[i]=str[i];
        i++;
    }
    return(key);
}

char *return_value(char *str)
{
    int i;
    char *value;

    i = 0;
    value = NULL;
    while(str[i] && str[i] != '=')
    {
        i++;
    }
    while(str[i])
    {
        value[i]=str[i];
        i++;
    }
    return(value);
}

char *to_append(char *str)
{
    int i;

    i = 0;
    while(str[i] && str[i]!='=')
    {
        i++;
    }
    return(str+i);
}

void add_var_if_not_exist(char *new_var, int size, int added)
{
    int i;

    i = 0;
    while(i < size+added)
    {
        i++;
    }
    if(ft_strch(new_var, '=') == -1)
    {
        environ[i] = ft_strdup(new_var);
    }
    else
        environ[i] = var_with_quotes(new_var);
}