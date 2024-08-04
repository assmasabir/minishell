#include "../minishell.h"

int ft_strch(char *str, char c)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == c)
            return(0);
        i++;
    }
    return(-1);
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

char *ft_strncpy(char *str1, char *str2, int n)
{
    int i;

    i = 0;
    while(str1[i] && i < n)
    {
        str2[i] = str1[i];
        i++;
    }
    str2[i] = '\0';
    return(str2);
}