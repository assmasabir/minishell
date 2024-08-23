
#include "../minishell.h"

int case_input(t_params *par, int *outfile, int* infile)
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
        perror(NULL); //add filename like bash
        if(*outfile != 1)
            close(*outfile);
        return(-1);
    }
    return(0);
}

int case_heredoc(t_params *par, int *infile)
{
    int fd;

    if(*infile != 0)
        close(*infile);           
    *infile = open_heredoc(par->files);
    if(*infile == -1)
    {
        perror(NULL); //add filename like bash
        return(-1);
    }
    close(*infile);
    fd = open("heredoc", O_RDWR, 0744);
    if(fd == -1)
        return(-1);
    return(0);
}

int case_normal_output(t_params *par, int *outfile)
{
    if(*outfile != 1)
        close(*outfile);
    *outfile = open(par->files->name, O_CREAT | O_RDWR | O_TRUNC, 0744);
    if(*outfile == -1)
    {
        perror(NULL); //add filename like bash
        return(-1);
    }
    return(0);
}

int case_append_output(t_params *par, int *outfile)
{
    if(*outfile != 1)
        close(*outfile);
    *outfile = open(par->files->name, O_CREAT | O_RDWR | O_APPEND, 0744);
    if(*outfile == -1)
    {
        perror(NULL); //add filename like bash
        return(-1);
    }
    return(0);
}

//if there is input file without < then others with it we take that first
int parse_files(t_params *par, int *outfile, int *infile)
{
    while(par->files)
    {
        if(par->files->type == 1)//unput
        {
            if(case_input(par, outfile, infile) == -1)
                return(-1);
        }
        else if(par->files->type == 2)//input heredoc
        {
            if(case_heredoc(par, infile) == -1)
                return(-1);
        }
        else if(par->files->type == 3)//output
        {
            if(case_normal_output(par, outfile) == -1)
                return(-1);
        }
        else if(par->files->type == 4)//output append
        {
            if(case_append_output(par, outfile) == -1)
                return(-1);
        }
        par->files = par->files->next;
    }
    return(0);
}
