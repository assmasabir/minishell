
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

void case_first(t_params *par, int i, int infile, int outfile)
{
    char *path_variable;
    int cmd_type;
    printf("i am here\n");
    cmd_type = cmdType(par);
    if(search_cmd(par->cmd[0], &path_variable) == -1 && cmd_type == 0)
    {
        //!free_and_exit();
    }
    if(outfile == 1 && par->nb_nodes != 1)
    {
        if(cmd_type == 0)
            child_process(par, infile , par->fd[i][1], path_variable);
        else
            redirect_cmd(par, cmd_type, par->fd[i][1]);
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
        if(cmd_type == 0)
            child_process(par, infile, outfile, path_variable);
        else
            redirect_cmd(par, cmd_type, outfile);
    }
}

void case_middle(t_params *par, int i,int infile, int outfile)
{
    char *path_variable;
    int cmd_type;

    cmd_type = cmdType(par);
    if(search_cmd(par->cmd[0], &path_variable) == -1 && cmd_type == 0)
    {
        //!free_and_exit();
    }
    if(outfile == 1 && infile == 0)
    {
        if(cmd_type == 0)
            child_process(par, par->fd[i][0], par->fd[i+1][1], path_variable);
        else
            redirect_cmd(par, cmd_type, par->fd[i+1][1]);
    }
    else if(outfile == 1 && infile != 0)
    {
        if(cmd_type == 0)
            child_process(par, infile, par->fd[i+1][1], path_variable);
        else
            redirect_cmd(par, cmd_type, par->fd[i+1][1]);
    }
    else if(outfile != 1 && infile == 0)
    {
        if(cmd_type == 0)
            child_process(par, par->fd[i][0], outfile,path_variable);
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

void case_last(t_params *par, int i,int infile, int outfile)
{
    char *path_variable;
    int cmd_type;

    cmd_type = cmdType(par);
    if(cmd_type != 0)
        redirect_cmd(par, cmd_type, outfile);
    else
    {    
        if(search_cmd(par->cmd[0], &path_variable) == -1)
        {
            //!free_and_exit();
        }
        if(infile == 0)

            child_process(par, par->fd[i][0] , outfile, path_variable);
        else 
            child_process(par, infile, outfile, path_variable);
    }
}

void open_pipes(t_params *par, int nb_pipes)
{
    int i;
    
    i = 0;
    while(i != nb_pipes)
    {
        if(pipe(par->fd[i]) == -1)
        {
            //!free and exit
        }
        i++;
    }
}

void close_all(t_params *par)
{
    int i;

    i = 0;
    if(par->nb_nodes == 1)
        return;
    while(par->fd[i])
    {
        close(par->fd[i][0]);
        close(par->fd[i][1]);
        i++;
    }
}

void manage_files(t_params *par)
{
    int i;
    int outfile;
    int infile;
    int nb_pipes;
    t_params* temp;

    temp = par;
    par->nb_nodes = list_size(par);
    printf("%d\n", par->nb_nodes);
    nb_pipes = par->nb_nodes -1;
    allocate_array(par, nb_pipes);
    open_pipes(par, nb_pipes);
    i = 0;
    while(par)
    {
        outfile = 1;
        infile = 0;
        if(parse_files(par, &outfile, &infile) == -1)
        {
            //!free and exit
        }
        else
        {
            // if(i < nb_pipes)
            // {
                if(i == 0)
                    case_first(par, i, infile, outfile);
                if(i != nb_pipes - 1 && nb_pipes != 0)
                    case_middle(par, i, infile, outfile);
                if(i == nb_pipes - 1 && nb_pipes != 0)
                    case_last(par, i, infile, outfile);
            // }
        }
        par= par->next;
        i++;
    }
    close_all(temp);
}