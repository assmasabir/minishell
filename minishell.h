#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

extern char **environ;

typedef struct Files
{
    int type;
    char *name;
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

typedef struct Cd
{
    char **cmd;
} t_cd;

int list_size(t_params *param);
int ft_strcmp(char *str1, char *str2);
int ft_strncmp(char *str1, char *str2, int n);
char **ft_split(char *str);
int ft_strchr(char *str, char c);



void ft_putstr(char *str, int fd);
int ft_strlen(char *str);
char *ft_join(char *str1, char *str2);
char *ft_strdup(char *str);
void free_matrix(char **str);
int check_if_append(char *new_var);
int check_if_add_change_append(t_params *par,char *new_var, int max, int *count);
int check_if_valid(char *new_var);
char **handle_variables(t_params *par, int output);
char *return_key(char* str);
int count_variables(t_params *par, int size);
char *to_append(char *str);
char **create_copy(char **str, int *size);
int size_env(char **env);
void loop(t_params *par, int size_env, char **export, char **cpy_env);
char **sort_env(t_params *par, char **export);
void add_var_if_not_exist(char *new_var, int size, int added, int check);
int check_if_var_reapeated(t_params *par, char *new_var);
void ft_putstr_exp(char *str, int fd);
char *add_non_existing_append_var(char *new_var);
void change_or_append_var_value(char *new_var, int check);
void change_value(char *new_var, int i);
void append_value(char *new_var, int i);
char *ft_strncpy(char *str1, char *str2, int n);
char	*get_next_line(int fd);
char	*ft_strcpy(char *dest, const char *src);
char	*free_and_join(char **reserve, char *buff);
#endif
