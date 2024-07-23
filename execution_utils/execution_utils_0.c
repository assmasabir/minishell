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

char *ft_strdup(char *str)
{
    char *cp;
    int i;
    
    i = 0;

    cp = malloc(sizeof(char)*(ft_strlen(str)+1));
    while(str[i])
    {
        cp[i]=str[i];
        i++;
    }
    cp[i] = '\0';
    return(cp);
}

char *ft_join(char *str1, char *str2)
{
    int i;
    int j;
    char *to_join;

    i = 0;
    j = 0;
    to_join = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
    while(str1[i])
    {
        to_join[i] = str1[i];
        i++;
    }
    while(str2[j])
    {
        to_join[i] = str2[j];
        i++;
        j++;
    }
    to_join[i] = '\0';
    return(to_join);
}