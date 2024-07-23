#include "../minishell.h"


char **create_copy(char **str, int *size)
{
    int i;
    char **cp;

    while(str[*size])
        (*size)++;
    cp = malloc(sizeof(char *)*(*size+1));
    i = 0;
    while(str[i])
    {
        cp[i]= ft_strdup(str[i]);
        i++;
    }
    cp[i]= NULL;
    return(cp);
}

void loop_over_env(char **cpy_env, char *small, int *index_of_small, int size_env)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while(i < size_env)
    {
        count++;
        while(cpy_env[i] && cpy_env[i][0] == '0')
            i++;
        if(cpy_env[i] && count == 1)
        {
            *index_of_small = i;
            small = cpy_env[i++];
        }
        if(environ[i] && ft_strcmp(small, cpy_env[i]) > 0 && cpy_env[i][0] != '0')
        {
            small = cpy_env[i];
            *index_of_small = i;
        }
        i++;
    }
}

void loop(int size_env, char **export, char **cpy_env)
{
    int j;
    int index_of_small;
    char *small;

    j = 0;
    small = NULL;
    index_of_small = 0;
    while(j < size_env && environ)
    {
        loop_over_env(cpy_env, small, &index_of_small, size_env);
        export[j] = ft_join("declare -x ", environ[index_of_small]);
        free(cpy_env[index_of_small]);
        cpy_env[index_of_small]=ft_strdup("0");
        j++;
    }
}

char **sort_env(char **export)
{
    int size_env;
    char **cpy_env;



    size_env = 0;
    cpy_env = create_copy(environ, &size_env);
    // free_matrix(export);
    export = malloc(sizeof(char *)*(size_env+1));
    loop(size_env, export, cpy_env);
    export[size_env]=NULL;
    free_matrix(cpy_env);
    return(export);
}
// int parse_first(char *str)
// {
    
// }

// void parse_exp(t_params *par)
// {
//     int i;

//     if(par->cmd[1][0]=='=')
//         //?print not valid identifier
 
// }
int count_variables(t_params *par)
{
    int i;
    int nb;

    i = 1;
    nb = 0;
    while(par->cmd[i])
    {
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
void *modify_existing_var(char *str)
{
    char *

}
char *modify_var(char *var, char *new_var, int append)
{
    int i;
    char *value;
    char *temp;

    i = 0;
    if(append == 0)
    {
        if(ft_strch(new_var, '=') == 0) //tiene que estar parseado antes
        {
            free(var);
            var = ft_strdup(new_var);
        }
        else
        {
            free(var);
            var = add_quotes(new_var);
        }
    }
    else
    {
        temp = var;
        var = ft_join(var, to_append(new_var));
        free(temp);
    }
    return(var);
}
// si es valido returna 0 sino returna -1
//si puedes arreglar el caso /
int check_if_valid(char *new_var) //!rje3
{
    int i;

    i = 0;
    while(new_var[i] == ' ')
        i++;
    if(new_var[i] == '#')
        return(-2);
    else if(new_var[i] == '$')
        return(-3);
    else if((new_var[i] < 'a' || new_var[i] > 'z') && (new_var[i] != '_'))
        return(-1);
    
    return(0);
}

//*si no tiene = no entra
//*no olvides el caso en el que se le da empty string a=""
char *add_quotes(char *new_var)
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

char **handle_variables_to_add(t_params *par)
{
    char **copy;
    int size;
    int i;
    int nb;
    int j;
    
    i = 0;
    j = 1;
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
        if(check_if_valid(environ[i]) == 0)
        {
            
        }
        else if(check_if_valid(environ) == -1)
        {
            print_error_do_not_exit(environ[i]);
            i++;
        }
        else if(check_if_valid(environ[i])==-2)
        {
            free_and_exit_without_printing_error();
        }
        else if(check_if_valid(environ[i]))
            i++;
    }
    environ[i] = NULL;
    free_matrix(copy);
    return(environ); 
}


void ft_export(t_params *par, int foutput)
{
    int i;
    int found;
    char **export;

    i = 0;
    found = 0;
    // si empieza con # no importa lo que viene a continuacion lista los variables
    // si # viene al principio de una variable al centro, guarda los de antes y sale
    // si $ viene al principio y es solo lista export
    // si $ viene con otros variables skip y guarda lo de antes y despues
    if(par->cmd[1] == NULL || par->cmd[1][0] == '#' || (par->cmd[1][0] == "$" && par->cmd[2]==NULL))
    {
        export = sort_env(environ);
        while(export[i])
        {
            ft_putstr(export[i], foutput);
            i++;
        }
        free_matrix(export);
    }
    else if(par->cmd[1])
    {
       environ = handle_variables_to_add(par);
       i++;
    }
}

int main(int argc, char **argv)
{
    // int i;
    char *new_ev;
    (void)argc;
    (void)argv;

    // i = 0;
    char *str= "";
    new_ev = add_quotes(str);
    printf("%s\n", new_ev);

}