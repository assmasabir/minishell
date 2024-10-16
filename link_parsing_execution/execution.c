/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:35:27 by asabir            #+#    #+#             */
/*   Updated: 2024/10/03 23:20:38 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_exit_status(t_line_splited *head)
{
	t_redirection	*temp;

	temp = head->redirection;
	while (temp)
	{
		if (temp->redirection_type)
			return ;
		temp = temp->next;
	}
	g_exit_status_value = 0;
}

void	set_exit_status(t_cmd_track *c_track, int pid)
{
	int	status;

	if (c_track->cmd_type == 0 && pid != -1)
	{
		waitpid(pid, &status, 0);
		if (status == 2 && g_exit_status_value != 131)
			g_exit_status_value = 130;
		else if (g_exit_status_value != 131)
			g_exit_status_value = status >> 8;
	}
}

void	execution(t_line_splited *head, t_cmd_track *c_track)
{
	c_track->nb_pipes = list_size(head) - 1;
	c_track->name_heredoc = NULL;
	c_track->leave = 0;
	allocate_array(c_track);
	if (open_pipes(c_track) == -1)
		return ;
	c_track->i = 0;
	while (head)
	{
		execute_pipes(&head, c_track);
		if (c_track->leave == 1)
			break ;
		c_track->i++;
	}
	while (wait(NULL) != -1)
		;
	close_all(c_track);
	free_array(c_track->fd, c_track->nb_pipes);
}
