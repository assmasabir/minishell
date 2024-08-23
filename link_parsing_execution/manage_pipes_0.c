#include "/nfs/homes/asabir/Desktop/minishell/minishell.h"

void case_first_builtin(t_params *par, int outfile, t_pipe_track *p_track)
{
    if(outfile == 1 && p_track->nb_pipes != 0)
        redirect_cmd(par, p_track->cmd_type, p_track->fd[p_track->i][1]);
    else if(outfile == 1 && p_track->nb_pipes == 0)
        redirect_cmd(par, p_track->cmd_type, 1);
    else
        redirect_cmd(par, p_track->cmd_type, outfile);
}

void case_first_executable(t_params *par, int infile, int outfile, t_pipe_track *p_track, char *path_variable)
{
    if(outfile == 1 && p_track->nb_pipes != 0)
        child_process(par, infile , p_track->fd[p_track->i][1], path_variable);
    else if(outfile == 1 && p_track->nb_pipes == 0)
        child_process(par, infile , 1, path_variable);
    else
        child_process(par, infile, outfile, path_variable);
}

void case_first(t_params *par, t_pipe_track *p_track, int infile, int outfile)
{
    char *path_variable;

    path_variable = NULL;
    p_track->cmd_type = cmdType(par);
    if(p_track->cmd_type == 0)
    {
        if(search_cmd(par->cmd[0], &path_variable) == -1)
            return;
        case_first_executable(par, infile, outfile, p_track, path_variable);
    }
    else
        case_first_builtin(par, outfile, p_track);

}

void loop_over_nodes(t_pipe_track* p_track, t_params **par, int infile, int outfile)
{
    if(parse_files(*par, &outfile, &infile) == -1)
        case_failed_parsing_files(p_track, par);
    else
    {
        if(p_track->i == 0)
        {
            case_first(*par, p_track, infile, outfile);
            *par= (*par)->next;
        }
        if(p_track->i != p_track->nb_pipes - 1 && p_track->nb_pipes != 0 && par)
        {
            case_middle(*par, p_track, infile, outfile);
            *par= (*par)->next;
        }
        if(p_track->i == p_track->nb_pipes - 1 && p_track->nb_pipes != 0 && par)
        {
            case_last(*par, p_track, infile, outfile);
            *par= (*par)->next;
        }
    }
}

void execution(t_params *par)
{
    int outfile;
    int infile;
    t_pipe_track *p_track;

    p_track = malloc(sizeof(t_pipe_track));
    p_track->nb_pipes = list_size(par) - 1;
    allocate_array(p_track);
    open_pipes(p_track);
    p_track->i = 0;
    while(par)
    {
        outfile = 1;
        infile = 0;
        loop_over_nodes(p_track, &par, infile, outfile);
        p_track->i++;
    }
    close_all(p_track);
    free_all(p_track);
}