#include "/home/elite/Desktop/minishell/minishell.h"

void free_array(t_pipe_track *p)
{
    int i;

    i = 0;
    while(i < p->nb_pipes)
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

void free_all(t_pipe_track * p_track)
{
    free_array(p_track);
    free(p_track);
}

// void free_nodes(void *pt)
// {
//     while(pt->next)
//     {

//     }
// }