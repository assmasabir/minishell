
#include "../minishell.h"

int open_heredoc(t_files *file)
{
    int fd;
    char *str;

    file->name = ft_join(file->name, "\n");
    fd = open("heredoc", O_CREAT | O_TRUNC | O_RDWR, 0644);
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
//if there is input file without < then others with it we take that first
int parse_files(t_params *par, int *outfile, int *infile)
{
    while(par->files)
    {
        printf("%p\n", par->files);
        if(par->files->type == 1)//unput
        {
            if(*infile != 0)
                close(*infile);
            *infile = open(par->files->name, O_RDONLY, 0744);
            if(*infile == -1 )
            {
                while(par->files)
                {
                    if(par->files->type == 2)//input heredoc
                        *infile = open_heredoc(par->files);
                    par->files = par->files->next;
                    unlink("heredoc");
                }
                perror(NULL);
                if(*outfile != 1)
                    close(*outfile);
                return(-1);
            }
        }
        else if(par->files->type == 2)//input heredoc
        {
            if(*infile != 0)
                close(*infile);           
            *infile = open_heredoc(par->files);
        }
        else if(par->files->type == 3)//output
        {
            if(*outfile != 1)
                close(*outfile);
            printf("Imhere\n");
            *outfile = open(par->files->name, O_CREAT | O_RDWR | O_TRUNC, 0744);
        }
        else if(par->files->type == 4)//output append
        {
            if(*outfile != 1)
                close(*outfile);
            *outfile = open(par->files->name, O_CREAT | O_RDWR | O_APPEND, 0744);
        }
        par->files = par->files->next;
    }
    return(0);
}

void case_first(t_params *par, t_pipe_track *p_track, int infile, int outfile)
{
    char *path_variable;
    int cmd_type;
    printf("first case\n");
    cmd_type = cmdType(par);
    if(cmd_type == 0 && search_cmd(par->cmd[0], &path_variable) == -1 )
    {   
        printf("error type should free");
        exit(5);
        //!free_and_exit();
    }
    if(outfile == 1 && par->nb_nodes != 1)
    {
        // printf("fiiiile %d\n", fd[0][0]);
        // printf("pipe %d\n", fd[i][1]);
        if(cmd_type == 0)
            child_process(par, infile , p_track->fd[p_track->i][1], path_variable);
        else
            redirect_cmd(par, cmd_type, p_track->fd[p_track->i][1]);
    }
    else if(outfile == 1 && par->nb_nodes == 1)
    {
        if(cmd_type == 0)
            child_process(par, infile , 1, path_variable);
        else
            redirect_cmd(par, cmd_type, 1);
    }
    else
    {
        printf("type : %d\n",cmd_type);
        if(cmd_type == 0)
            child_process(par, infile, outfile, path_variable);
        else
            redirect_cmd(par, cmd_type, outfile);
    }

}

void case_middle(t_params *par, t_pipe_track *p_track, int infile, int outfile)
{
    char *path_variable;
    int cmd_type;

    printf("middle case\n");
    cmd_type = cmdType(par);
    if(search_cmd(par->cmd[0], &path_variable) == -1 && cmd_type == 0)
    {
        //!free_and_exit();
    }
    if(outfile == 1 && infile == 0)
    {
        if(cmd_type == 0)
            child_process(par, p_track->fd[p_track->i][0], p_track->fd[p_track->i+1][1], path_variable);
        else
            redirect_cmd(par, cmd_type, p_track->fd[p_track->i+1][1]);
    }
    else if(outfile == 1 && infile != 0)
    {
        if(cmd_type == 0)
            child_process(par, infile, p_track->fd[p_track->i+1][1], path_variable);
        else
            redirect_cmd(par, cmd_type, p_track->fd[p_track->i+1][1]);
    }
    else if(outfile != 1 && infile == 0)
    {
        if(cmd_type == 0)
            child_process(par, p_track->fd[p_track->i][0], outfile,path_variable);
        else
            redirect_cmd(par, cmd_type, outfile);
    }
    else
    {
        if(cmd_type == 0)
            child_process(par, infile, outfile, path_variable);
        else
            redirect_cmd(par, cmd_type, outfile);
    }
}

void case_last(t_params *par, t_pipe_track *p_track, int infile, int outfile)
{
    // printf(" iam file descriptors 00000 %p\n",par->fd);
    char *path_variable;
    int cmd_type;

    printf("last case\n");
    cmd_type = cmdType(par);
    if(cmd_type != 0)
        redirect_cmd(par, cmd_type, outfile);
    else
    {    
        if(search_cmd(par->cmd[0], &path_variable) == -1)
        {
            //!free_and_exit();
            printf("cmd not herre lalala\n");
        }
        printf("path_variable in case last %s\n", path_variable);
        if(infile == 0)
        {
            // printf("iiiiii %d \n", fd[0][0]);
            child_process(par, p_track->fd[p_track->i][0] , outfile, path_variable);
            // printf("infile : %d outfile : %d\n",p÷, outfile);
        }
        else {
            child_process(par, infile, outfile, path_variable);
        }
    }
}

void open_pipes(t_pipe_track *p, int nb_pipes)
{
    int i;
    
    i = 0;
    printf("nub pip %d :  \n", nb_pipes);
    while(i != nb_pipes)
    {
        if(pipe(p->fd[i]) == -1)
        {
            printf("!free and exit");
        }
        i++;
    }
    
}

void close_all(t_pipe_track *p, int nb_nodes)
{
    int i;

    i = 0;
    if(nb_nodes == 1)
        return;
    while(p->fd[i])
    {
        close(p->fd[i][0]);
        close(p->fd[i][1]);
        i++;
    }
}

void manage_files(t_params *par)
{
    int outfile;
    int infile;
    int nb_pipes;
    t_pipe_track *p_track;

    p_track = malloc(sizeof(t_pipe_track));
    par->nb_nodes = list_size(par);
    printf("%d\n", par->nb_nodes);
    nb_pipes = par->nb_nodes -1;
    allocate_array(p_track, nb_pipes);
    open_pipes(p_track, nb_pipes);
    p_track->i = 0;
    while(par)
    {
        outfile = 1;
        infile = 0;
        if(parse_files(par, &outfile, &infile) == -1)
        {
            printf("hdgus\n");
            exit(34456);
            //!free and exit
        }
        else
        {
            // printf(" iam file descriptors %d %d\n", par->fd[0][0], par->fd[0][1]);

            if(p_track->i == 0)
            {
                case_first(par, p_track, infile, outfile);
                par= par->next;
            }
            if(p_track->i != nb_pipes - 1 && nb_pipes != 0 && par)
            {
                case_middle(par, p_track, infile, outfile);
                par= par->next;
            }
            if(p_track->i == nb_pipes - 1 && nb_pipes != 0 && par)
            {
                
                case_last(par, p_track, infile, outfile);
                par= par->next;
            }
        }
        p_track->i++;
    }
    close_all(p_track, par->nb_nodes);
}