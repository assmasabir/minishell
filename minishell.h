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

typedef struct Exprot
{
    char *key;
    char *value;
    struct Export *next;
} t_export;

//executable utils
int list_size(t_params *param);
int ft_strcmp(char *str1, char *str2);
int ft_strncmp(char *str1, char *str2, int n);
char **ft_split(char *str);
int ft_strch(char *str, char c);


//built_in utils
void ft_putstr(char *str, int fd);
int ft_strlen(char *str);
char *uppercase(char *name);
char *ft_join(char *str1, char *str2);
char *ft_strdup(char *str);
void free_matrix(char **str);
char *modify_var(char *var, char *new_var, int append);
#endif
