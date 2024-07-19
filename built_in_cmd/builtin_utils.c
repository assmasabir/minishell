#include "../minishell.h"

void ft_putstr(char *str, int fd)
{
    int i;

    i = 0;
    while(str[i])
    {
        write(fd, &str[i], 1);
        i++;
    }
}

int ft_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;
    while(str1[i] && str2[i])
    {
        if(str1[i]==str2[i])
            i++;
        else
            break;
    }
    return(str1[i]- str2[i]);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        i++;
    }
    return(i);
}