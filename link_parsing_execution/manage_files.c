
#include "../minishell.h"

int open_heredoc(t_files *file)
{
    int fd;
    char *str;

    file->name = ft_join(file->name, "\n");
    fd = open("heredoc", O_CREAT | O_TRUNC | O_RDWR, 644);
    while(1)
    {
        str = get_next_line(STDIN_FILENO);
        if(ft_strcmp(str, file->name) == 0 || str == NULL)
        {
            free(str);
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
            *outfile = open(par->files->name, O_RDONLY, 744);
            if(*outfile == -1 )
            {
                while(par->files)
                {
                    if(par->files->type == 2)//input heredoc
                        *outfile = open_heredoc(par->files);
                    par->files = par->files->next;
                }
                perror(NULL);
                return(-1);
            }
        }
        else if(par->files->type == 2)//input heredoc
            *outfile = open_heredoc(par->files);
        else if(par->files->type == 3)//output
            *infile = open(par->files->name, O_CREAT | O_RDWR | O_TRUNC, 744);
        else if(par->files->type == 4)//output append
            *infile = open(par->files->name, O_CREAT | O_RDWR | O_APPEND, 744);
        par->files = par->files->next;
    }
    return(0);
}

void case_first(t_params *par, int i, int infile, int outfile)
{
    
}

void case_middle(t_params *par, int *i,int infile, int outfile)
{

}

void case_last(t_params *par, int *i,int infile, int outfile)
{
    
}

int manage_files(t_params *par)
{
    int i;
    int outfile;
    int infile;
    int nb_pipes;

    par->nb_nodes = list_size(par);
    allocate_array(par, nb_pipes);
    nb_pipes = par->nb_nodes -1;
    i = 0;

    while(par)
    {
        outfile = 1;
        infile = 0;
        if(parse_files(par, &outfile, &infile) == -1)
        {
            //free and exit
        }
        else
        {
            if(i < nb_pipes)
            {
                if(i == 0)
                    case_first(par, i, infile, outfile);
                if(i != nb_pipes - 1)
                    case_middle(par, &i, infile, outfile);
                if(i == nb_pipes - 1)
                    case_last(par, &i, infile, outfile);
            }
        }
        par= par->next;
    }
}