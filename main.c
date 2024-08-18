
#include "/nfs/homes/asabir/Desktop/minishell/minishell.h"

int main()
{
    // int out = 1;
    // int in = 0;
    t_params* tpar = malloc(sizeof(t_params));
    tpar->cmd = malloc(2*sizeof(int *));
    tpar->cmd[0] = "env";
    tpar->cmd[1] = NULL;
    tpar->files = malloc(sizeof(t_files));
    tpar->files->name = "test1";
    tpar->files->type = 3;
    tpar->files->next = malloc(sizeof(t_files));
    tpar->files->next->name = "test2";
    tpar->files->next->type = 3;
    tpar->files->next->next = malloc(sizeof(t_files));
    tpar->files->next->next->name = "lim";
    tpar->files->next->next->type = 3;
    tpar->files->next->next->next = malloc(sizeof(t_files));
    tpar->files->next->next->next->name = "test3";
    tpar->files->next->next->next->type = 3;
    tpar->files->next->next->next->next = malloc(sizeof(t_files));
    tpar->files->next->next->next->next->name = "im";
    tpar->files->next->next->next->next->type = 3;
    tpar->files->next->next->next->next->next = NULL;
    tpar->next = NULL;
    manage_files(tpar);

    // free(tpar->files);
    // printf("%d\n", tpar->files->type);
    free(tpar->cmd);
    free(tpar);
}