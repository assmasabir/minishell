#include "minishell.h"

int main()
{
    char *buff;

    buff = NULL;
    buff = getcwd(buff, 0);
    printf("%s\n", buff);
}