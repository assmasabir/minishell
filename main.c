
#include "/home/elite/Desktop/minishell/minishell.h"


int main(int argc, char **argv)
{
    t_params  *par;
    int i;

    i = 0;
    (void)argc;
    (void)argv;
    par = malloc(sizeof(t_params));
    par->cmd = malloc(7 * sizeof(char *));
    if (par->cmd == NULL) {
        return 1;
    }
    par->cmd[0] = ft_strdup("export");
    par->cmd[1] = ft_strdup("?ngurpp");
    par->cmd[2] = ft_strdup("_uuuuu=hoooooiiii");
    par->cmd[3] = ft_strdup("?uuuuu=aaaa");
    par->cmd[4] = ft_strdup("PWD+=lfkifjr");
    par->cmd[5] = ft_strdup("?VSCODE_INJECTION+=miaw");
    par->cmd[6] = NULL;
    ft_export(par, 1);
    while(environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }
    i = 0;
    while(par->cmd[i])
    { 
        free(par->cmd[i]);
        i++;
    }
    free(par);
}