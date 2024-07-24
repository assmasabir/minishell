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

char *ft_join_var(char *str1, char *str2)
{
    int i;
    int j;
    char *to_join;

    i = 0;
    j = 0;
    to_join = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
    while(str1[i])
    {
        if(str1[i] == '"' && str1[i+1] == '\0')
            break;
        to_join[i] = str1[i];
        i++;
    }
    while(str2[j])
    {
        to_join[i] = str2[j];
        i++;
        j++;
    }
    to_join[i] = '"';
    to_join[i+1] = '\0';
    return(to_join);
}

int main()
{
    printf("%s\n", ft_join_var("assma=\"sab\"", "ir"));
}