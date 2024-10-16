/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:32:01 by asabir            #+#    #+#             */
/*   Updated: 2024/10/03 23:50:12 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_file_helper(t_cmd_track *c_track, t_redirection *tmp, int *infile,
		int *outfile)
{
	if (tmp->redirection_type == 2)
	{
		if (case_heredoc(tmp, c_track, infile) == -1)
		{
			if (g_exit_status_value == 130)
				c_track->leave = 1;
			return (-1);
		}
	}
	else if (tmp->redirection_type == 3)
	{
		if (case_normal_output(tmp, outfile) == -1)
			return (-1);
	}
	else
	{
		if (case_append_output(tmp, outfile) == -1)
			return (-1);
	}
	return (0);
}

int	parse_files_of_a_single_node(t_line_splited *head, t_cmd_track *c_track,
		int *infile, int *outfile)
{
	t_redirection	*tmp;

	tmp = head->redirection;
	update_exit_status(head);
	while (tmp)
	{
		if (tmp->redirection_type == 1)
		{
			if (case_input(tmp, c_track, infile) == -1)
				return (-1);
		}
		else if (parse_file_helper(c_track, tmp, infile, outfile) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int	case_input_helper(t_cmd_track *c_track, int *fd, t_redirection *redirection,
		char *file_name)
{
	*fd = open_heredoc(c_track, redirection);
	if (*fd == -1)
		return (free(file_name), -1);
	close(*fd);
	*fd = 1;
	return (0);
}

int	case_input(t_redirection *redirection, t_cmd_track *c_track, int *infile)
{
	int		fd;
	char	*file_name;

	if (*infile != 0)
		close(*infile);
	fd = open(redirection->file_limiter, O_RDONLY, 0644);
	if (fd == -1)
	{
		file_name = ft_strdup(redirection->file_limiter);
		while (redirection)
		{
			if (redirection->redirection_type == 2)
			{
				if (case_input_helper(c_track, &fd, redirection,
						file_name) == -1)
					return (-1);
			}
			redirection = redirection->next;
		}
		my_perror(NULL, file_name, 1);
		free(file_name);
		return (-1);
	}
	*infile = fd;
	return (0);
}

int	case_heredoc(t_redirection *redirection, t_cmd_track *c_track, int *infile)
{
	int	fd;

	if (*infile != 0)
		close(*infile);
	fd = open_heredoc(c_track, redirection);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open(c_track->name_heredoc, O_RDWR, 0744);
	if (fd == -1)
	{
		custom_error("minishell: error in opening file descriptor\n", 1);
		return (-1);
	}
	*infile = fd;
	free(c_track->name_heredoc);
	return (0);
}
