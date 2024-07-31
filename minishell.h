#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>


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
    char **myenv;
    struct Params *next;
    
} t_params;

typedef struct Exprot
{
    char *key;
    char *value;
    struct Export *next;
} t_export;

int list_size(t_params *param);
int ft_strcmp(char *str1, char *str2);
int ft_strncmp(char *str1, char *str2, int n);
char **ft_split(char *str);
int ft_strch(char *str, char c);



void ft_putstr(char *str, int fd);
int ft_strlen(char *str);
char *uppercase(char *name);
char *ft_join(char *str1, char *str2);
char *ft_strdup(char *str);
void free_matrix(char **str);
void *modify_existing_var(t_params *par, char *str);
int check_if_append(char *new_var);
int check_if_add_change_append(t_params *par,char *new_var, int max, int *count);
int check_if_valid(char *new_var);
char *var_with_quotes(char *new_var);
char *ft_join_var(char *str1, char *str2);
char **handle_variables(t_params *par, int output);
char *return_key(char* str);
char *return_value(char *str);
int count_variables(t_params *par, int size);
char *to_append(char *str);
char **create_copy(char **str, int *size);
int size_env(char **env);
void loop(t_params *par, int size_env, char **export, char **cpy_env);
char **sort_env(t_params *par, char **export);
void add_var_if_not_exist(t_params *par, char *new_var, int size, int added);
int check_if_var_reapeated(t_params *par, char *new_var);
void ft_putstr_exp(char *str, int fd);
#endif
