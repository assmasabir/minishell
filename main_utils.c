/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:11:09 by asabir            #+#    #+#             */
/*   Updated: 2024/10/05 19:51:11 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_required_variables(t_cmd_track *c_track, char **env)
{
	c_track->size_env = 0;
	c_track->myenv = create_copy(c_track, env, &c_track->size_env);
	c_track->home = return_value_env_if_exists(c_track, "HOME");
	c_track->pwd = return_value_env_if_exists(c_track, "PWD");
	if (c_track->pwd == NULL)
		c_track->pwd = getcwd(c_track->pwd, 0);
	reset_shlvl(c_track);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status_value = 130;
}

void	set_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = &handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	minishell(t_cmd_track *c_track, char *line)
{
	t_line_splited		*head;

	if (!parsing(line, &head, c_track->myenv))
	{
		execution(head, c_track);
		free_everything(head);
	}
}

void	free_required_variables(t_cmd_track *c_track)
{
	free(c_track->pwd);
	free(c_track->home);
	free_matrix(c_track->myenv);
	free(c_track);
}
