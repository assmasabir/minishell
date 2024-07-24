#include <../../minishell.h>

void *modify_var(char *new_var, int check)
{
    int i;
    char *key_var;

    i = 0;
    key_var = return_key(new_var);
    while(environ[i])
    {
        if(ft_strcmp(return_key(environ[i]),key_var) == 0)
            break;
        i++;
    }
    environ[i]=modify_var(environ[i], str, 0);
}

void change_or_append_var_value(char *new_var, int check)
{
    int i;
    char *value;
    char *temp;
    char *key_var;

    i = 0;
    key_var = return_key(new_var);
    while(environ[i])
    {
        if(ft_strcmp(return_key(environ[i]),key_var) == 0)
            break;
        i++;
    }
    if(check == 1) //change
    {
        if(ft_strch(new_var, '=') == -1)
        {
            free(environ[i]);
            environ[i] = ft_strdup(new_var);
        }
        else
        {
            free(environ[i]);
            environ[i] = var_with_quotes(new_var);
        }
    }
    else if(check == 2) //append
    {
        temp = environ[i];
        environ[i] = ft_join_var(environ[i], to_append(new_var));
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

char **handle_variables(t_params *par)
{
    char **copy;
    int size;
    int i;
    int nb;
    int j;
    int check;
    int count_added;
    
    i = 0;
    j = 1;
    count_added = 0;
    nb = count_variables(par);
    size = size_enb(environ);
    copy = create_copy(environ, &size);
    free_matrix(environ);
    environ = malloc(sizeof(char *)*(nb+size+1));
    while(i < size)
    {
        environ[i]=copy[i];
        i++;
    }
    while(i < (nb+size))
    {
        if(check_if_valid(environ[i]) == 0)//valid
        {
            check = check_if_add_change_append(par->cmd[i]);
            if(check == 0)//add
            {
                add_var_if_not_exist(par->cmd[i], size, count_added);
                count_added++;
            }
            else if(check == 1)//change
                change_or_append_var_value(par->cmd[i], check);
            else if(check == 2)//append
                change_or_append_var_value(par->cmd[i], check);
        }
        else if(check_if_valid(par->cmd[i]) == -1)//other like * or = ...
        {
            print_error_do_not_exit(par->cmd[i]);
            i++;
        }
        // else if(check_if_valid(par->cmd[i]) == -2)//$
        //     i++;
        else if(check_if_valid(par->cmd[i]) == -3)//#
            free_and_exit_without_printing_error(); 
        i++;
    }
    environ[i] = NULL;
    free_matrix(copy);
    return(environ); 
}
