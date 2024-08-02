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
void ft_putstr_exp(char *str, int fd)
{
    int i;
    int check;

    i = 0;
    check = 0;
    while(str[i])
    {
        if(str[i] == '=')
        {
            write(fd, &str[i], 1);
            check = 1;
            write(fd, "\"", 1);
            i++;
        }
        if(str[i])
            write(fd, &str[i], 1);
        else
            break;
        i++;
    }
    if(check ==1)
        write(fd, "\"", 1);
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

