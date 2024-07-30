#include "/home/elite/Desktop/minishell/minishell.h"

//0 es decir append
int check_if_append(char *new_var)
{
    int i;

    i = 0;
    while(new_var[i])
    {
        if(new_var[i] == '+' && new_var[i+1] == '=')
            return(0);
        i++;
    }
    return(-1);
}

//0 es decir add
//1 es decir change
//2 es decir append
int check_if_add_change_append(t_params *par, char *new_var, int max)
{
    int i;
    int check;
    char *keyenv;
    char *keyvar;

    i = 0;
    check = 0;
    while(i < max-1)
    {
        if(new_var[0] == '$')
            return(-1);
        keyenv = return_key(par->myenv[i]);
        keyvar = return_key(new_var);
        // printf("%s\n", par->myenv[i]);
        // printf("%s'n", keyenv);
        // printf("%s'n", keyvar);
        if(ft_strcmp(keyenv, keyvar) == 0)
        {
            printf("hhhh\n");
            check = 1;
            break;
        }
        i++;
    }
    free(keyenv);
    free(keyvar);
    if(check == 0)
        return (0);
    if(check == 1 && check_if_append(new_var) != 0)
        return(1);
    if(check == 1 && check_if_append(new_var) == 0)
        return(2);
    return(-1);
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
        return(-3);
    else if(new_var[i] == '$')
        return(-2);
    else if((new_var[i] < 'a' || new_var[i] > 'z') && (new_var[i] != '_'))
        return(-1);
    return(0);
}