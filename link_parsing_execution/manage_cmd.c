/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:38:22 by asabir            #+#    #+#             */
/*   Updated: 2024/10/01 20:26:31 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	determine_type(t_line_splited *head)
{
	if (ft_strcmp(head->cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(head->cmd[0], "cd") == 0)
		return (2);
	else if (ft_strcmp(head->cmd[0], "pwd") == 0)
		return (3);
	else if (ft_strcmp(head->cmd[0], "unset") == 0)
		return (4);
	else if (ft_strcmp(head->cmd[0], "export") == 0)
		return (5);
	else if (ft_strcmp(head->cmd[0], "env") == 0)
		return (6);
	else if (ft_strcmp(head->cmd[0], "exit") == 0)
		return (7);
	else
		return (0);
}

int	redirect_cmd(t_line_splited *head, int infile, int outfile,
		t_cmd_track *c_track)
{
	update_command_env(c_track, head->cmd[0]);
	if (c_track->cmd_type == 0)
		return (executable_cmd(head, c_track, infile, outfile));
	else if (c_track->cmd_type == 1)
		ft_echo(head, outfile);
	else if (c_track->cmd_type == 2)
		ft_cd(head, c_track, outfile);
	else if (c_track->cmd_type == 3)
		ft_pwd(c_track, outfile);
	else if (c_track->cmd_type == 4)
		ft_unset(head, c_track);
	else if (c_track->cmd_type == 5)
		ft_export(head, c_track, outfile);
	else if (c_track->cmd_type == 6)
		ft_env(c_track, outfile);
	else if (c_track->cmd_type == 7)
		ft_exit(head, c_track);
	return (-1);
}
