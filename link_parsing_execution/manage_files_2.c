/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:19:37 by asabir            #+#    #+#             */
/*   Updated: 2024/10/05 20:14:16 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	case_normal_output(t_redirection *redirection, int *outfile)
{
	int	fd;

	if (*outfile != 1)
		close(*outfile);
	fd = open(redirection->file_limiter, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
	{
		my_perror(NULL, redirection->file_limiter, 1);
		return (-1);
	}
	*outfile = fd;
	return (0);
}

int	case_append_output(t_redirection *redirection, int *outfile)
{
	int	fd;

	if (*outfile != 1)
		close(*outfile);
	fd = open(redirection->file_limiter, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fd == -1)
	{
		my_perror(NULL, redirection->file_limiter, 1);
		return (-1);
	}
	*outfile = fd;
	return (0);
}

void	handle_sigint_child_process(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	handle_sigint_here_doc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

void	update_sigint(int flag)
{
	struct sigaction	sa_int;

	if (flag)
	{
		sa_int.sa_handler = SIG_IGN;
		sa_int.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa_int, NULL);
	}
	else
	{
		sa_int.sa_handler = &handle_sigint_here_doc;
		sa_int.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa_int, NULL);
	}
}
