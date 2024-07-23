#include "../minishell.h"

int ft_strch(char *str, char c)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == c)
            return(1);
        i++;
    }
    return(0);
}

void free_matrix(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}