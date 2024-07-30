 #include "/nfs/homes/asabir/Desktop/minishell/minishell.h"

int check_if_var_reapeated(t_params *par, char *new_var)
{
    int i;

    i = 1;
    while(par->cmd[i])
    {
        if(ft_strcmp(par->cmd[i], new_var) == 0)
            i++;
        if(par->cmd[i] && ft_strcmp(return_key(par->cmd[i]), return_key(new_var)) == 0)
            return(1);
        if(!par->cmd[i])
            break;  
        i++;
    }
    return(0);
}

int count_variables(t_params *par,int size)
{
    int i;
    int nb;
    int count;
    // int how_many_repeated_keys;

    i = 1;
    nb = 0;
    count = 0;
    // how_many_repeated_keys = 0;
    while(par->cmd[i])
    {
        printf("iiiiiiii\n");
        // if(check_if_var_reapeated(par, i) == 1)
        //     how_many_repeated_keys++;
        if(check_if_add_change_append(par, par->cmd[i], size, &count) == 0)
        {
            nb++;
        }
        i++;
    }
    // nb += how_many_repeated_keys/2;
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
    // printf("heeere\n");
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

void add_var_if_not_exist(t_params *par, char *new_var, int size, int added)
{
    int i;

    i = 0;
    while(i < size+added)
    {
        i++;
    }
    if(ft_strch(new_var, '=') == -1)
    {
        par->myenv[i] = ft_strdup(new_var);
    }
    else
        par->myenv[i] = var_with_quotes(new_var);
}