/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:06:08 by asabir            #+#    #+#             */
/*   Updated: 2024/10/04 18:56:54 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	executable_cmd(t_line_splited *head, t_cmd_track *c_track, int infile,
		int outfile)
{
	int	pid;

	if (search_cmd(head->cmd[0], &c_track->path_variable, c_track) == -1)
		return (-1);
	pid = child_process(head, infile, outfile, c_track);
	if (c_track->path_variable)
		free(c_track->path_variable);
	return (pid);
}

int	search_cmd(char *cmd, char **path_variable, t_cmd_track *c_track)
{
	int		check;
	char	*full_path;
	char	**paths;

	full_path = find_path(c_track);
	if (parse_cmd(cmd) == -1)
		return (-1);
	paths = ft_split(full_path, ':');
	check = is_cmd_present(paths, cmd, path_variable);
	free_matrix(paths);
	if (check == -2)
		return (-1);
	if (check == -1)
		return (handle_cmd_not_found(cmd));
	else
		return (0);
	return (-1);
}

int	is_cmd_present(char **paths, char *cmd, char **path_variable)
{
	int		i;
	char	*join;
	char	*temp;

	i = 0;
	if (ft_strchr(cmd, '/') == 0)
		return (is_it_a_directory_or_executable(cmd, path_variable));
	else
	{
		while (paths && paths[i])
		{
			temp = ft_join(paths[i], "/");
			join = ft_join(temp, cmd);
			if (access(join, X_OK) == 0)
			{
				*path_variable = join;
				free(temp);
				return (0);
			}
			free_two_arrays(temp, join);
			i++;
		}
	}
	return (-1);
}
