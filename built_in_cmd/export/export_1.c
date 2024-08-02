 #include "/nfs/homes/asabir/Desktop/minishell/minishell.h"

char *add_non_existing_append_var(char *new_var)
{
    char *str;
    int i;
    int j;

    i = 0;
    j = 0;
    str = malloc(ft_strlen(new_var));
    while(new_var[i])
    {
        if(new_var[i] == '+')
            i++;
        str[j] = new_var[i];
        i++;
        j++;
    }
    str[j]='\0';
    return(str);
}

void change_value(char *new_var, int i)
{
    if(ft_strch(new_var, '=') == -1)
    {
        free(environ[i]);
        environ[i] = ft_strdup(new_var);
    }
    else
    {
        free(environ[i]);
        environ[i] = ft_strdup(new_var);
    }
}

void append_value(char *new_var, int i)
{
    char *temp;

    temp = environ[i];
    environ[i] = ft_join(environ[i], to_append(new_var));
    free(temp);
}

void change_or_append_var_value(char *new_var, int check)
{
    int i;
    char *key_var;
    char *key_env;

    i = 0;
    key_var = return_key(new_var);
    while(environ[i])
    {   
        key_env = return_key(environ[i]);
        if(ft_strcmp(key_env,key_var) == 0)
        {
            free(key_env);
            break;
        }
        i++;
        free(key_env);
    }
    if(check == 1) //change
        change_value(new_var, i);
    else if(check == 2) //append
        append_value(new_var, i);
    free(key_var);
}

char **handle_variables(t_params *par, int output)
{
    char **copy;
    int size;
    int i;
    int nb;
    int check;
    int count_added;
    int j;
    int duplicated_keys;
    
    i = 0;
    duplicated_keys = 0;
    count_added = 0;
    size = size_env(environ);
    nb = count_variables(par, size);
    copy = create_copy(environ, &size);
    environ = malloc(sizeof(char *)*(nb+size+1));
    while(copy[i])
    {
        environ[i]=copy[i];
        i++;
    }
    j = 1;
    
    free(copy);
    while(par->cmd[j])
    {
        if(check_if_valid(par->cmd[j]) == 0)//valid
        {
            check = check_if_add_change_append(par, par->cmd[j], i+1, &duplicated_keys);
            printf("i am check%d\n", check);
            if(check == 0)//add
            {
                add_var_if_not_exist(par->cmd[j], size, count_added, check);
                count_added++;
            }
            else if(check == 1)//change
            {
                change_or_append_var_value(par->cmd[j], check);
            }
            else if(check == 2)//append
            {
                change_or_append_var_value(par->cmd[j], check);
            }
            else if(check == 3)
            {
                add_var_if_not_exist(par->cmd[j], size, count_added, check);
                count_added++;
            }
        }
        else if(check_if_valid(par->cmd[j]) == -1)//other like * or = ...
        {
            write(output, "error\n", 6);
            // err_check = 1;
            i--;
        }
        // else if(check_if_valid(par->cmd[i]) == -2)//$
        //     i++;
        else if(check_if_valid(par->cmd[j]) == -3)//#
            exit(127);
        // free_and_exit_without_printing_error();
        if(par->cmd[j][0] != '$')
            i++;
        j++;
    }
    i = i - duplicated_keys - 1;
    environ[i] = NULL;
    return(environ); 
}
