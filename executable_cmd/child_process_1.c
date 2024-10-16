/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:22:22 by asabir            #+#    #+#             */
/*   Updated: 2024/10/03 23:53:15 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_cmd(char *cmd)
{
	if (ft_strcmp(cmd, "!") == 0)
	{
		g_exit_status_value = 1;
		return (-1);
	}
	else if (ft_strcmp(cmd, ".") == 0)
	{
		ft_putstr_fd("bash: .: filename argument required\n.", 2);
		custom_error(": usage: . filename [arguments]\n", 2);
		return (-1);
	}
	else if (ft_strcmp(cmd, "..") == 0 || cmd[0] == '\0')
	{
		printf("Command '%s' not found\n", cmd);
		g_exit_status_value = 127;
		return (-1);
	}
	return (0);
}

int	handle_cmd_not_found(char *cmd)
{
	printf("%s: command not found\n", cmd);
	g_exit_status_value = 127;
	return (-1);
}

int	is_it_a_directory_or_executable(char *cmd, char **path_variable)
{
	void	*dir;

	dir = opendir(cmd);
	if (dir != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" Is a directory\n", 2);
		g_exit_status_value = 126;
		closedir(dir);
		return (-2);
	}
	*path_variable = ft_strdup(cmd);
	return (0);
}

char	*find_path(t_cmd_track *c_track)
{
	int	i;

	i = 0;
	if (c_track->myenv == NULL)
		return (NULL);
	while (c_track->myenv[i])
	{
		if (ft_strncmp(c_track->myenv[i], "PATH=", 5) == 0)
			return (c_track->myenv[i] + 5);
		i++;
	}
	return (NULL);
}

void	ft_perror(char *ptr)
{
	perror(ptr);
	exit(-1);
}
