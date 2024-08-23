#include "/nfs/homes/asabir/Desktop/minishell/minishell.h"

void case_failed_parsing_files(t_pipe_track *p_track, t_params **par)
{
    if(p_track->nb_pipes == 0)
    {
        free_all(p_track);
        exit(EXIT_FAILURE);
    }
    else
        *par = (*par)->next;
}

void case_middle_built_in(t_params *par, int infile, int outfile, t_pipe_track *p_track)
{
    if(outfile == 1 && infile == 0)
        redirect_cmd(par, p_track->cmd_type, p_track->fd[p_track->i+1][1]);
    else if(outfile == 1 && infile != 0)
        redirect_cmd(par, p_track->cmd_type, p_track->fd[p_track->i+1][1]);
    else if(outfile != 1 && infile == 0)
        redirect_cmd(par, p_track->cmd_type, outfile);
    else
        redirect_cmd(par, p_track->cmd_type, outfile);
}

void case_middle_executable(t_params *par, int infile, int outfile, t_pipe_track *p_track, char *path_variable)
{
    if(outfile == 1 && infile == 0)
        child_process(par, p_track->fd[p_track->i][0], p_track->fd[p_track->i+1][1], path_variable);
    else if(outfile == 1 && infile != 0)
        child_process(par, infile, p_track->fd[p_track->i+1][1], path_variable);
    else if(outfile != 1 && infile == 0)
        child_process(par, p_track->fd[p_track->i][0], outfile,path_variable);
    else
        child_process(par, infile, outfile, path_variable);
}

void case_middle(t_params *par, t_pipe_track *p_track, int infile, int outfile)
{
    char *path_variable;

    path_variable = NULL;
    p_track->cmd_type = cmdType(par);
    if(p_track->cmd_type == 0)
    {
        if(search_cmd(par->cmd[0], &path_variable) == -1)
            return;
        case_middle_executable(par, infile, outfile, p_track, path_variable);
    }
    else
        case_middle_built_in(par, infile, outfile, p_track);
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