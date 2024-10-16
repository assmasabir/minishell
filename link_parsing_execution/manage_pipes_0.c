/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:35:23 by asabir            #+#    #+#             */
/*   Updated: 2024/10/08 20:45:51 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pipes(t_line_splited **head, t_cmd_track *c_track)
{
	if (c_track->i == 0)
		first_case(head, c_track);
	if (head && c_track->i != c_track->nb_pipes - 1 && c_track->nb_pipes != 0
		&& !c_track->leave)
		middle_case(head, c_track);
	if (head && c_track->i == c_track->nb_pipes - 1 && c_track->nb_pipes != 0
		&& !c_track->leave)
		last_case(head, c_track);
}

void	first_case(t_line_splited **head, t_cmd_track *c_track)
{
	int	infile;
	int	outfile;
	int	pid;

	infile = 0;
	outfile = 1;
	if (parse_files_of_a_single_node(*head, c_track, &infile, &outfile) != -1)
	{
		if ((*head)->cmd[0])
		{
			c_track->cmd_type = determine_type(*head);
			if (outfile == 1 && c_track->nb_pipes != 0)
				pid = redirect_cmd((*head), infile, c_track->fd[c_track->i][1],
						c_track);
			else if (outfile == 1 && c_track->nb_pipes == 0)
				pid = redirect_cmd((*head), infile, 1, c_track);
			else
				pid = redirect_cmd((*head), infile, outfile, c_track);
			if (!c_track->nb_pipes)
				set_exit_status(c_track, pid);
		}
	}
	close_files_after_use(infile, outfile, c_track, 0);
	(*head) = (*head)->next;
}

void	middle_case(t_line_splited **head, t_cmd_track *c_track)
{
	int	infile;
	int	outfile;

	infile = 0;
	outfile = 1;
	if (parse_files_of_a_single_node((*head), c_track, &infile, &outfile) != -1)
	{
		if ((*head)->cmd[0])
		{
			c_track->cmd_type = determine_type((*head));
			if (infile == 0 && outfile == 1)
				(void)redirect_cmd(*head, c_track->fd[c_track->i][0],
					c_track->fd[c_track->i + 1][1], c_track);
			else if (infile != 0 && outfile == 1)
				(void)redirect_cmd(*head, infile, c_track->fd[c_track->i
					+ 1][1], c_track);
			else if (infile == 0 && outfile != 1)
				(void)redirect_cmd(*head, c_track->fd[c_track->i][0], outfile,
					c_track);
			else
				(void)redirect_cmd(*head, infile, outfile, c_track);
		}
	}
	close_files_after_use(infile, outfile, c_track, 1);
	*head = (*head)->next;
}

void	last_case(t_line_splited **head, t_cmd_track *c_track)
{
	int	infile;
	int	outfile;
	int	pid;

	infile = 0;
	outfile = 1;
	if (parse_files_of_a_single_node(*head, c_track, &infile, &outfile) != -1)
	{
		if ((*head)->cmd[0])
		{
			c_track->cmd_type = determine_type(*head);
			if (infile == 0)
				pid = redirect_cmd(*head, c_track->fd[c_track->i][0], outfile,
						c_track);
			else
				pid = redirect_cmd(*head, infile, outfile, c_track);
			set_exit_status(c_track, pid);
		}
	}
	close_files_after_use(infile, outfile, c_track, 0);
	close(c_track->fd[c_track->i][0]);
	*head = (*head)->next;
}
