 #include "/nfs/homes/asabir/Desktop/minishell/minishell.h"

// void *modify_var(char *new_var, int check)
// {
//     int i;
//     char *key_var;

//     i = 0;
//     key_var = return_key(new_var);
//     while(par->myenv[i])
//     {
//         if(ft_strcmp(return_key(par->myenv[i]),key_var) == 0)
//             break;
//         i++;
//     }
//     par->myenv[i]=modify_var(par->myenv[i], str, 0);
// }

void change_or_append_var_value(t_params* par,char *new_var, int check)
{
    int i;
    char *temp;
    char *key_var;

    i = 0;
    key_var = return_key(new_var);
    while(par->myenv[i])
    {
        if(ft_strcmp(return_key(par->myenv[i]),key_var) == 0)
            break;
        i++;
    }
    if(check == 1) //change
    {
        if(ft_strch(new_var, '=') == -1)
        {
            // printf("ddijfidjf\n");
            free(par->myenv[i]);
            par->myenv[i] = ft_strdup(new_var);
        }
        else
        {
            printf("dfhdufho %s\n", par->myenv[i]);
            free(par->myenv[i]);
            par->myenv[i] = var_with_quotes(new_var);
        }
    }
    else if(check == 2) //append
    {
        temp = par->myenv[i];
        printf("top %s\n", to_append(new_var));
        par->myenv[i] = ft_join_var(par->myenv[i], to_append(new_var));
        free(temp);
    }
}

//*si no tiene = no entra
//*no olvides el caso en el que se le da empty string a=""
char *var_with_quotes(char *new_var)
{
    char *new_var_with_quotes;
    int i;
    int j;

    i = 0;
    new_var_with_quotes = malloc(ft_strlen(new_var)+3);
    while(new_var[i] && new_var[i] != '=')
    {
        new_var_with_quotes[i]= new_var[i];
        i++;
    }
    new_var_with_quotes[i++] = '=';
    j = i;
    new_var_with_quotes[i++] = '"';
    while(new_var[j])
    {
        new_var_with_quotes[i]=new_var[j++];
        i++;
    }
    new_var_with_quotes[i++] = '"';
    new_var_with_quotes[i]= '\0';
    return(new_var_with_quotes);
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
    size = size_env(par->myenv);
    nb = count_variables(par, size);
    copy = create_copy(par->myenv, &size);
    printf("i am here %d\n", nb);
    // free_matrix(par->myenv);
    par->myenv = malloc(sizeof(char *)*(nb+size+1));
    while(copy[i])
    {
        par->myenv[i]=copy[i];
        i++;
    }
    j = 1;
    // int v = 0;
    // while(copy[v])
    // {
    //     printf("%s\n", par->myenv[v]);
    //     v++;
    //     printf("i am v %d\n",v);
    // }
    int max = nb+size;
    // int b = 1;
    // while(par->cmd[b])
    // {
    //     printf("cmd %s\n", par->cmd[b]);
    //     b++;
    // }
    free(par);
    printf("cmd %s\n", par->cmd[i]);
    while(i < max)
    {
        printf("test\n");
        if(check_if_valid(par->cmd[j]) == 0)//valid
        {
            check = check_if_add_change_append(par, par->cmd[j], i+1, &duplicated_keys);
            printf("i am check%d\n", check);
            if(check == 0)//add
            {
                printf("add var\n");
                add_var_if_not_exist(par, par->cmd[j], size, count_added);
                count_added++;
            }
            else if(check == 1)//change
            {
                change_or_append_var_value(par, par->cmd[j], check);
            }
            else if(check == 2)//append
            {
                change_or_append_var_value(par, par->cmd[j], check);
            }
        }
        else if(check_if_valid(par->cmd[j]) == -1)//other like * or = ...
        {
            // print_error_do_not_exit(par->cmd[i]);
            write(output, "error\n", 6);
            i++;
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
    if(duplicated_keys != 0)
        i = i - duplicated_keys;
    par->myenv[i] = NULL;
    // free_matrix(copy);
    return(par->myenv); 
}
