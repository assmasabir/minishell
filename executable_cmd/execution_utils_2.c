#include "../minishell.h"

int ft_strch(char *str, char c)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == 'c')
            return(1);
        i++;
    }
    return(0);
}