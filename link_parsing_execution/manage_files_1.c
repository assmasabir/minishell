#include "../minishell.h"

int open_heredoc(t_files *file)
{
    int fd;
    char *str;

    file->name = ft_join(file->name, "\n");
    fd = open("heredoc", O_CREAT | O_TRUNC | O_RDWR, 0644);
    if(fd == -1)
    {
        perror(NULL);
        return(-1);
    }
    while(1)
    {
        str = get_next_line(STDIN_FILENO);
        if(ft_strcmp(str, file->name) == 0 || str == NULL)
        {
            free(str);
            free(file->name);
            return(fd);
        }
        ft_putstr(str, fd);
        free(str);
    }
    return(fd);
}

void close_all(t_pipe_track *p)
{
    int i;

    i = 0;
    if(p->nb_pipes == 0)
        return;
    while(i < p->nb_pipes - 1)
    {
        close(p->fd[i][0]);
        close(p->fd[i][1]);
        i++;
    }
}

void open_pipes(t_pipe_track *p)
{
    int i;
    
    i = 0;
    while(i != p->nb_pipes)
    {
        if(pipe(p->fd[i]) == -1)
        {
            printf("!free and exit");
        }
        i++;
    }
    
}
