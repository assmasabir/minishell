/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_descriptors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:25:33 by asabir            #+#    #+#             */
/*   Updated: 2024/10/08 20:46:00 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_pipes(t_cmd_track *c_track)
{
	int	i;

	i = 0;
	while (i != c_track->nb_pipes)
	{
		if (pipe(c_track->fd[i]) == -1)
		{
			printf("error in while opening a pipe\n");
			g_exit_status_value = -1;
			return (-1);
		}
		i++;
	}
	return (0);
}

void	close_files_after_use(int infile, int outfile, t_cmd_track *c_track,
		int check_if_middle)
{
	if (c_track->nb_pipes != 0)
	{
		if (check_if_middle == 1)
		{
			close(c_track->fd[c_track->i + 1][1]);
			close(c_track->fd[c_track->i][0]);
		}
		else
			close(c_track->fd[c_track->i][1]);
	}
	if (infile != 0)
		close(infile);
	if (outfile != 1)
		close(outfile);
}

void	close_fds(t_cmd_track *c_track, int infile, int outfile)
{
	int	i;

	i = 0;
	while (i < c_track->nb_pipes)
	{
		if (c_track->fd[i][0] == infile || c_track->fd[i][1] == outfile)
		{
			if (c_track->fd[i][0] == infile)
			{
				close(c_track->fd[i][1]);
				i++;
			}
			else if (c_track->fd[i][1] == outfile)
			{
				close(c_track->fd[i][0]);
				i++;
			}
		}
		else
		{
			close(c_track->fd[i][0]);
			close(c_track->fd[i][1]);
			i++;
		}
	}
}

void	close_all(t_cmd_track *c_track)
{
	int	i;

	i = 0;
	if (c_track->nb_pipes == 0)
		return ;
	while (i < c_track->nb_pipes)
	{
		close(c_track->fd[i][0]);
		close(c_track->fd[i][1]);
		i++;
	}
}

void	free_array(int **fd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
