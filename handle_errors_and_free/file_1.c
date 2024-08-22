#include "/nfs/homes/asabir/Desktop/minishell/minishell.h"

free_array(t_pipe_track *p, int nb_pipes)
{
    int i;

    i = 0;
    while(i < nb_pipes)
    {
        free(p->fd[i]);
        i++;
    }
    free(p->fd);
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

// void free_nodes(void *pt)
// {
//     while(pt->next)
//     {

//     }
// }