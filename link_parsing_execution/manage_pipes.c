#include "/nfs/homes/asabir/Desktop/minishell/minishell.h"

void case_first(t_params *par, t_pipe_track *p_track, int infile, int outfile)
{
    char *path_variable;
    int cmd_type;

    cmd_type = cmdType(par);
    if(cmd_type == 0 && search_cmd(par->cmd[0], &path_variable) == -1 )
        return;
    if(outfile == 1 && par->nb_nodes != 1)
    {
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

    cmd_type = cmdType(par);
    if(search_cmd(par->cmd[0], &path_variable) == -1 && cmd_type == 0)
        return;
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
    char *path_variable;
    int cmd_type;

    cmd_type = cmdType(par);
    if(cmd_type != 0)
        redirect_cmd(par, cmd_type, outfile);
    else
    {    
        if(search_cmd(par->cmd[0], &path_variable) == -1)
            return;
        if(infile == 0)
            child_process(par, p_track->fd[p_track->i][0] , outfile, path_variable);
        else
            child_process(par, infile, outfile, path_variable);
    }
}

void open_pipes(t_pipe_track *p, int nb_pipes)
{
    int i;
    
    i = 0;
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
    while(i < nb_nodes - 1)
    {
        close(p->fd[i][0]);
        close(p->fd[i][1]);
        i++;
    }
}

void execution(t_params *par)
{
    int outfile;
    int infile;
    int nb_pipes;
    t_pipe_track *p_track;

    p_track = malloc(sizeof(t_pipe_track));
    par->nb_nodes = list_size(par);
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
            exit(34456);
            //!free and exit
        }
        
        else
        {
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
    close_all(p_track, nb_pipes + 1);
    free_array(p_track, par->nb_nodes - 1);
    free(p_track);
    free_matrix(par->cmd);
    free(par);
}