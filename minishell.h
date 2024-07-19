#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

extern char ** environ;

typedef struct Files
{
    int type;
    char *name_file;
    struct Files *next;
} t_files;

typedef struct Params
{
    char **cmd;
    char *args;
    char **env;
    t_files *files;
    int nb_nodes;
    int *fd;
    int fd_pos;
    struct Params *next;
    
} t_params;

//executable utils
int list_size(t_params *param);
int ft_strcmp(char *str1, char *str2);
int ft_strncmp(char *str1, char *str2, int n);
char **ft_split(char *str);
int ft_strch(char *str, char c);

//built_in utils
void ft_putstr(char *str, int fd);
int ft_strlen(char *str);
#endif
