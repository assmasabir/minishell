/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:06:11 by asabir            #+#    #+#             */
/*   Updated: 2024/10/08 20:36:22 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigquit_child_process(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 1);
	g_exit_status_value = 131;
}

void	update_sigint_sigquit(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = &handle_sigint_child_process;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = &handle_sigquit_child_process;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

int	child_process(t_line_splited *head, int infile, int outfile,
		t_cmd_track *c_track)
{
	int	id;

	update_sigint_sigquit();
	id = fork();
	if (id == -1)
		my_perror(NULL, NULL, 1);
	if (id == 0)
	{
		close_fds(c_track, infile, outfile);
		if (dup2(outfile, STDOUT_FILENO) == -1)
			ft_perror(NULL);
		if (outfile != 1)
			close(outfile);
		if (dup2(infile, STDIN_FILENO) == -1)
			ft_perror(NULL);
		if (infile != 0)
			close(infile);
		execve(c_track->path_variable, head->cmd, c_track->myenv);
		free_array(c_track->fd, c_track->nb_pipes);
		my_perror(NULL, c_track->path_variable, 0);
		exit(g_exit_status_value);
	}
	return (id);
}
