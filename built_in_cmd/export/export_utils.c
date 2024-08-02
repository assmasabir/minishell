 #include "/nfs/homes/asabir/Desktop/minishell/minishell.h"

int check_if_var_reapeated(t_params *par, char *new_var)
{
    int i;
    char *key_cmd;
    char *key_new_var;

    i = 1;
    key_new_var = return_key(new_var);
    while(par->cmd[i])
    {
        key_cmd = return_key(par->cmd[i]);
        if(ft_strcmp(par->cmd[i], new_var) == 0)
            i++;
        if(par->cmd[i] && ft_strcmp(key_cmd, key_new_var) == 0)
        {
            free(key_cmd);
            free(key_new_var);
            return(1);
        }
        if(!par->cmd[i])
        {
            free(key_cmd);
            break;  
        }
        i++;
        free(key_cmd);
    }
    free(key_new_var);
    return(0);
}

int count_variables(t_params *par,int size)
{
    int i;
    int nb;
    int count;
    int check;

    i = 1;
    nb = 0;
    count = 0;
    while(par->cmd[i])
    {
        check = check_if_add_change_append(par, par->cmd[i], size, &count);
        if( check == 0 || check == 3)
        {
            nb++;
        }
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
    key = malloc(ft_strlen(str)+1);
    while(str[i] && str[i] != '=' && str[i] != '+')
    {
        key[i]=str[i];
        i++;
    }
    key[i]= '\0';
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
    while(str[i] && str[i] != '=')
    {
        i++;
    }
    i++;
    return(str+i);
}

void add_var_if_not_exist(char *new_var, int size, int added, int check)
{
    int i;

    i = 0;
    while(i < size+added)
    {
        i++;
    }
    if(check == 0)
        environ[i] = ft_strdup(new_var);
    else if(check == 3)
        environ[i] = add_non_existing_append_var(new_var);
}