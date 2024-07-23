#include "../minishell.h"

int list_size(t_params *param)
{
    int i;

    i = 0;

    while(param)
    {
        i++;
        param->next;
    }
    return (i);
}

int ft_strncmp(char *str1, char *str2, int n)
{
    int i;

    i = 0;
    while(str1[i] && str2[i] && i < n)
    {
        if(str1[i]==str2[i])
            i++;
        else
            break;
    }
    return(str1[i]- str2[i]);
}

int count_paths(char *str)
{
    int i;
    int count;

    i = 0;
    count = 1;
    while(str[i])
    {
        if(str[i] == ':')
            count++;
        i++;
    }
    return (count);
}

char **ft_split(char *str)
{
    int i;
    int size;
    char **to_return;
    int nb_paths;
    int n;

    i = 0;
    size = 0;
    to_return = malloc(sizeof(char*)*(count_paths(str)+1));
    while(i < nb_paths)
    {
        size = 0;
        n = 0;
        while(str[size] != ':' && str[size])
            size++;
        to_return[i] = malloc((size + 1));
        while(n < size)
        {
            to_return[i][n] = *str;
            n++;
            str++;
        }
        to_return[i][n] = '/0';
        i++;
    }
    to_return[i] = NULL;
    return(to_return);
}