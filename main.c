
#include "/Users/asabir/minishell/minishell.h"

int main()
{
    // int out = 1;
    // int in = 0;
    t_params* tpar = malloc(sizeof(t_params));
    tpar->cmd = malloc(3*sizeof(char *));
    tpar->cmd[0] = "echo";
    tpar->cmd[1] = "assma";
    tpar->cmd[2] = NULL;
    tpar->next = malloc(sizeof(t_params));
    tpar->next->cmd = malloc(2*sizeof(char *));
    tpar->next->cmd[0] = "cat";
    tpar->next->cmd[1] = NULL;
    tpar->next->files = NULL;
    tpar->files = NULL;
    // tpar->files->name = "test1";
    // tpar->files->type = 3;
    // tpar->files->next = NULL;
    // tpar->files->next->name = "test2";
    // tpar->files->next->type = 3;
    // tpar->files->next->next = malloc(sizeof(t_files));
    // tpar->files->next->next->name = "test3";
    // tpar->files->next->next->type = 3;
    // tpar->files->next->next->next = malloc(sizeof(t_files));
    // tpar->files->next->next->next->name = "test4";
    // tpar->files->next->next->next->type = 3;
    // tpar->files->next->next->next->next = malloc(sizeof(t_files));
    // tpar->files->next->next->next->next->name = "test5";
    // tpar->files->next->next->next->next->type = 3;
    // tpar->files->next->next->next->next->next = NULL;
    tpar->next->next = NULL;
    manage_files(tpar);

    // free(tpar->files);
    // printf("%d\n", tpar->files->type);
    free(tpar->cmd);
    free(tpar);

}