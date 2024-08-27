
#include "/nfs/homes/asabir/Desktop/minishell/minishell.h"

// int main()
// {
//     // int out = 1;
//     // int in = 0;
//     t_params* tpar = malloc(sizeof(t_params));
//     tpar->cmd = malloc(2*sizeof(char *));
//     tpar->cmd[0] = "env";
//     tpar->cmd[1] = NULL;
//     // tpar->cmd[2] = NULL;
//     tpar->next = malloc(sizeof(t_params));
//     tpar->next->cmd = malloc(2*sizeof(char *));
//     tpar->next->cmd[0] = "pwd";
//     tpar->next->cmd[1] = NULL;
//     tpar->next->next = malloc(sizeof(t_params));
//     tpar->next->next->cmd = malloc(2*sizeof(char*));
//     tpar->next->next->cmd[0] = "cat";
//     tpar->next->next->cmd[1] = NULL;
//     tpar->next->files = NULL;
//     tpar->next->next->files = malloc(sizeof(t_files));

//     tpar->next->next->files->name = "test3";
//     tpar->next->next->files->type = 2;
//     tpar->next->next->files->next = NULL;
//     // tpar->files->next->name = "test2";
//     // tpar->files->next->type = 3;
//     tpar->files = malloc(sizeof(t_files));
//     tpar->files->name = "test1";
//     tpar->files->type = 4;
//     tpar->files->next = NULL;


//     tpar->next->next->next = NULL;
//     execution(tpar);

//     // free(tpar->files);
//     // printf("%d\n", tpar->files->type);
//     free(tpar->cmd);
//     free(tpar);
// }
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
    par->cmd[1] = ft_strdup("?ngurp");
    par->cmd[2] = ft_strdup("uuuu=hoooooiiii");
    par->cmd[3] = ft_strdup("?uuuu=aaaa");
    par->cmd[4] = ft_strdup("uuuu+=lalala");
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