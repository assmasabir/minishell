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
    char **env;
    t_files *files;
    char **myenv;
    struct Params *next;
    
} t_params;


typedef struct Pipe_track
{
    int **fd;
    int i;
    int nb_pipes;
    int cmd_type;
    char *path_variable;
} t_pipe_track;


int list_size(t_params *param);
int ft_strcmp(char *str1, char *str2);
int ft_strncmp(char *str1, char *str2, int n);
char **ft_split(char *str,char c);
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
int count_new_variables(t_params *par, int size);
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
int search_cmd(char *cmd, char **path_variable);
void child_process(t_params* par, int infile, int outfile, char *path_variable);
void redirect_cmd(t_params *par, int type, int outfile);
int cmdType(t_params *par);
void ft_echo(t_params *par, int fd);
void ft_env(int fd);
void ft_pwd(int fd);
void ft_unset(t_params *par);
void ft_cd(t_params *par, int output);
void ft_exit();
void ft_export(t_params *par, int foutput);
void allocate_array(t_pipe_track *p);
int parse_files(t_params *par, int *outfile, int *infile);
char	*ft_strchrr(char *s, int c);
int		ft_strncmpp(char *s1, char *s2, unsigned int n);
void execution(t_params *par);
void free_all(t_pipe_track * p_track);
//handle_errors
void free_array(t_pipe_track *p);
int open_heredoc(t_files *file);
void close_all(t_pipe_track *p);
void open_pipes(t_pipe_track *p);
void case_failed_parsing_files(t_pipe_track *p_track, t_params **par);
void case_middle_built_in(t_params *par, int infile, int outfile, t_pipe_track *p_track);
void case_middle_executable(t_params *par, int infile, int outfile, t_pipe_track *p_track, char *path_variable);
void case_middle(t_params *par, t_pipe_track *p_track, int infile, int outfile);
void case_last(t_params *par, t_pipe_track *p_track, int infile, int outfile);
#endif
