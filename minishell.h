/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:16:08 by asabir            #+#    #+#             */
/*   Updated: 2024/10/05 19:54:23 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int					g_exit_status_value;

// structs--------------------------------------------------------
typedef struct s_redirection
{
	int						redirection_type;
	int						expand_in_here_doc_flag;
	char					*file_limiter;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_line_splited
{
	char					**cmd;
	char					**env;
	t_redirection			*redirection;
	char					**myenv;
	struct s_line_splited	*next;

}							t_line_splited;

typedef struct cmd_track
{
	int						**fd;
	int						i;
	int						nb_pipes;
	int						cmd_type;
	char					*path_variable;
	char					**myenv;
	int						count_added;
	int						size_env;
	char					*pwd;
	char					*home;
	int						dup_keys_in_splited_line;
	char					*name_heredoc;
	int						leave;
}							t_cmd_track;

// parsing----------------------------------------------------------
int							parsing(char *line, t_line_splited **head,
								char **env);
void						display_and_free(t_line_splited *head, char **env);
void						replace_spaces_with_space(char *str);
void						skip_until_find_match(char **str, char c);
int							quote_is_not_closed(char *line);
int							something_is_wrong(char *line);
int							with_pipes(char *line);
int							check_what_is_next(char *str);
int							with_redirections(char *line);
int							redirection_handler(char **str, char c);
char						**ft_split_quotes(char *s, char c);
void						free_matrix(char **line_splited);
void						set_up_for_execution(t_line_splited **head,
								char *line);
void						*safe_malloc(size_t size);
void						skip_until_find_match_index_version(char *str,
								int *i, char c);
void						copy_until_find_match(char **str, char c,
								char *dest, int *index);
void						ft_lstadd_line_splited(t_line_splited **lst,
								t_line_splited *new);
void						ft_lstadd_redirection(t_redirection **lst,
								t_redirection *new);
void						ft_extract_redirections_cmd(
								t_line_splited *empty_node, char *str);
void						redirection_output(char *tmp,
								t_line_splited *empty_node);
void						redirection_input(char *tmp,
								t_line_splited *empty_node);
void						fill_up_blank(t_line_splited *empty,
								int redirection_t, char *tmp);
char						*get_file_limiter(char *tmp);
void						copy_and_blank(char **str, char c, char *dest,
								int *index);
int							file_limiter_size(char *tmp);
void						free_everything(t_line_splited *head);
void						clean_each_node(t_line_splited *node);
void						free_redirection_list(t_redirection *head);
void						free_line_splited_list(t_line_splited *head);
void						display(t_line_splited *head);
int							expand_and_rm_quotes(t_line_splited **head,
								char **env);
void						expand_cmd(char **cmd, char **env);
int							is_alphanumeric(char c);
int							is_digit(char c);
int							is_space(char c);
char						*get_key(char **str);
char						*get_value(char *key, char **env, char **str);
char						*norminette1(char **str);
int							count_words_exam(char const *s);
int							how_many_strings(char **matrix);
char						*expand_and_leave_quotes(char *str, char **env,
								int i, char *tmp);
void						double_quotes_handler(char **str, char **new,
								int *i, char **env);
void						found_dolar_sign(char **str, char **new, int *i,
								char **env);
void						single_quotes_handler(char **str, char *new,
								int *i);
char						*ft_strjoin_pro(char *s1, char *s2, char *s3);
size_t						ft_strlcpy(char *dst, const char *src,
								size_t dstsize);
size_t						ft_strlcat(char *dst, const char *src,
								size_t dstsize);
char						**ft_split_with_white_spaces(char *s);
int							how_many_strings_in_triple_ptr(char ***ptr);
char						**join_matrices_ine_one_matrix(char ***tmp);
int							expand_redirection(t_redirection *head, char **env);
char						*rm_quotes_redirection(char *str);
int							non_here_doc_expand(t_redirection *node,
								char **env);
void						here_doc_expand(t_redirection *node);
char						*ft_strndup(const char *s1, size_t n);
char						*expand_line(char *line, t_cmd_track *c_track,
								int flag);
void						found_dolar_sign_inside_dq(char **str, char **new,
								int *i, char **env);
void						hide_double_single_quotes(char *value);
void						copy_whats_between_quotes(char **str, char c,
								char *new, int *i);
void						norminette2(char c, char *new, int *i, char **tmp);
void						copy_whats_between_quotes(char **str, char c,
								char *new, int *i);
char						*rm_quotes_redirection_heredoc(char *str,
								t_redirection *node);
void						set_signals(void);
void						minishell(t_cmd_track *c_track, char *line);
void						norminette3(char **str, int *i, char **new);
// builtin_cmd----------------------------------------------------
char						**create_copy(t_cmd_track *c_tarck, char **str,
								int *size);
void						ft_export(t_line_splited *head,
								t_cmd_track *c_track, int foutput);
char						**sort_env(t_cmd_track *c_track, char **export);
void						loop(t_cmd_track *c_track, char **export,
								char **cpy_env);
void						get_index_of_small(t_cmd_track *c_track,
								char **cpy_env, int *index_of_small);
int							return_size_env(t_cmd_track *c_track);
void						handle_absolute_paths(t_line_splited *head,
								t_cmd_track *c_track);
void						case_go_home(t_cmd_track *c_track, int tilde);
void						case_go_up(t_cmd_track *c_track);
void						case_go_back(t_cmd_track *c_track, int output);
void						change_variable(t_cmd_track *c_track,
								char *new_var);
void						change_directory(char *dir_to_access,
								t_cmd_track *c_track, char *oldpwd);
char						*parent_directory_path(char *current_dir);
void						directories_inside_current_directory(
								t_line_splited *head, t_cmd_track *c_track);
void						ft_cd(t_line_splited *head, t_cmd_track *c_track,
								int output);
char						*allocate_value(t_cmd_track *c_track, int i);
char						*return_value_env_if_exists(t_cmd_track *c_track,
								char *key);
void						set_required_variables(t_cmd_track *c_track,
								char **env);
void						ft_env(t_cmd_track *c_track, int fd);
void						ft_echo(t_line_splited *head, int fd);
void						case_dash_n(t_line_splited *head, int fd,
								int index);
void						ft_pwd(t_cmd_track *c_track, int fd);
int							check_if_key_exists(t_line_splited *head,
								t_cmd_track *c_track, int *i, int z);
void						reset_env(t_cmd_track *c_track, int j);
void						ft_unset(t_line_splited *head,
								t_cmd_track *c_track);
void						crazy_case_has_2nd_arg(t_line_splited *head);
void						crazy_case(t_line_splited *head);
void						exit_has_args(t_line_splited *head);
void						crazy_case_but_there_is_more(t_line_splited *head);
void						there_is_more(t_line_splited *head);
int							exit_status_is_acceptable(char *str);
void						ft_exit(t_line_splited *head, t_cmd_track *c_track);
int							create_new_environ(t_cmd_track *c_track,
								t_line_splited *head, int nb);
int							check_if_valid(t_cmd_track *c_track, char *new_var,
								int size, int added);
int							is_var_value_present(t_cmd_track *c_track,
								char *value, int size, int added);
int							check_if_key_already_exists(t_cmd_track *c_track,
								char *new_var, int max);
int							check_if_append(char *new_var);
int							check_if_add_change_append(t_line_splited *head,
								t_cmd_track *c_track, char *new_var, int max);
int							is_var_value_present(t_cmd_track *c_track,
								char *value, int size, int added);
void						escape_the_var_itself(t_line_splited *head,
								char *new_var, int *i, char **key_cmd);
int							check_if_var_reapeated(t_line_splited *head,
								char *new_var);
void						change_or_append_var_value(t_cmd_track *c_track,
								char *new_var, int check);
int							count_new_variables(t_cmd_track *c_track,
								t_line_splited *head, int size);
void						add_var_if_not_exist(t_cmd_track *c_track,
								char *new_var, int added, int check);
char						*return_key(char *str);
char						*return_value(char *full_var);
char						*add_non_existing_append_var(char *new_var);
void						change_value(t_cmd_track *c_track, char *new_var,
								int i);
void						append_value(t_cmd_track *c_track, char *new_var,
								int i);
void						update_pwd(t_cmd_track *c_track);
char						**handle_variables(t_line_splited *head,
								t_cmd_track *c_track);
void						handle_valid_variable(t_cmd_track *c_track,
								t_line_splited *head, int *index_of_next_var,
								int *j);
void						free_two_arrays(char *str1, char *str2);
void						add_non_existing_var_implicitly(
								t_cmd_track *c_track,
								t_line_splited *head, char *new_var);
void						go_back_helper(t_cmd_track *c_track,
								char *current_env, char *old_env, int output);
char						**create_mini_copy(t_cmd_track *c_track, int *size);
void						execute_pipes(t_line_splited **head,
								t_cmd_track *c_track);
void						case_go_home_helper(t_cmd_track *c_track,
								char *home_dir, char *current_dir);
int							look_for_var_index(t_cmd_track *c_track,
								char *key_var, int *i);
int							check_if_should_update(t_cmd_track *c_track,
								char *new_var, int size, int added);
void						update_c_track(t_line_splited *head,
								t_cmd_track *c_track, int *i);
int							exit_status_last_check(char *trimed);

// executable_cmd---------------------------------------------------
char						*find_path(t_cmd_track *c_track);
int							is_cmd_present(char **paths, char *cmd,
								char **path_variable);
int							search_cmd(char *cmd, char **path_variable,
								t_cmd_track *c_track);
int							child_process(t_line_splited *head, int infile,
								int outfile, t_cmd_track *c_track);
int							executable_cmd(t_line_splited *head,
								t_cmd_track *c_track, int infile, int outfile);
char						*to_append(char *str);
int							handle_cmd_not_found(char *cmd);
int							parse_cmd(char *cmd);
int							is_it_a_directory_or_executable(char *cmd,
								char **path_variable);
void						ft_perror(char *ptr);
void						update_sigint(int flag);
void						handle_sigint_here_doc(int sig);
void						handle_sigint_child_process(int sig);
// link_parsing_execution-----------------------------------------------
int							parse_files_of_a_single_node(t_line_splited *head,
								t_cmd_track *c_track, int *infile,
								int *outfile);
int							case_input(t_redirection *redirection,
								t_cmd_track *c_track, int *infile);
int							case_heredoc(t_redirection *redirection,
								t_cmd_track *c_track, int *infile);
int							case_normal_output(t_redirection *redirection,
								int *outfile);
int							case_append_output(t_redirection *redirection,
								int *outfile);
int							open_heredoc(t_cmd_track *c_track,
								t_redirection *redirection);
int							determine_type(t_line_splited *head);
int							redirect_cmd(t_line_splited *head, int infile,
								int outfile, t_cmd_track *c_track);
void						last_case(t_line_splited **head,
								t_cmd_track *c_track);
void						middle_case(t_line_splited **head,
								t_cmd_track *c_track);
void						first_case(t_line_splited **head,
								t_cmd_track *c_track);
void						set_exit_status(t_cmd_track *c_track, int pid);
void						execution(t_line_splited *head,
								t_cmd_track *c_track);
int							parse_file_helper(t_cmd_track *c_track,
								t_redirection *tmp, int *infile, int *outfile);

// execution_utils----------------------------------------------
int							list_size(t_line_splited *head);
void						ft_putstr_fd(char *str, int fd);
int							ft_strcmp(char *str1, char *str2);
void						my_perror(char *function_name, char *file_name,
								int exit_status);
void						custom_error(char *error_message, int exit_status);
void						allocate_array(t_cmd_track *c_track);
void						ft_putstr_exp(char *str, int fd);
int							ft_strlen(char *str);
char						*ft_strdup(char *str);
char						*ft_join(char *str1, char *str2);
char						**ft_split(char *str, char c);
int							count_paths(char *str, char c);
int							ft_strncmp(char *str1, char *str2, int n);
int							return_size_env(t_cmd_track *c_track);
int							ft_strchr(char *str, char c);
int							size_env(char **env);
void						close_all(t_cmd_track *c_track);
int							open_pipes(t_cmd_track *c_track);
void						close_files_after_use(int infile, int outfile,
								t_cmd_track *c_track, int check_if_middle);
void						close_fds(t_cmd_track *c_track, int infile,
								int outfile);
void						free_all(t_cmd_track *c_track);
char						*ft_strncpy(char *str1, char *str2, int n);
char						*ft_strtrim(char *s1, char *set);
unsigned int				ft_atou(const char *str);
char						*ft_itoa(int n);
void						update_exit_status(t_line_splited *head);
void						free_array(int **fd, int nb_pipes);
void						update_command_env(t_cmd_track *c_track, char *cmd);
void						handle_sigint_child_process(int sig);
void						handle_sigint_here_doc(int sig);
int							ft_atoi(const char *str);
int							check_if_shlvl_valid_nb(char *value);
void						reset_shlvl(t_cmd_track *c_track);
char						*return_key_for_check_if_valid(char *str);
void						handle_sigint(int sig);
void						free_required_variables(t_cmd_track *c_track);
#endif
