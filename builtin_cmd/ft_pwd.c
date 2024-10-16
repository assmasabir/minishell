/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 01:16:19 by asabir            #+#    #+#             */
/*   Updated: 2024/09/30 17:32:27 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(t_cmd_track *c_track)
{
	free(c_track->pwd);
	c_track->pwd = return_value_env_if_exists(c_track, "PWD");
}

char	*allocate_value(t_cmd_track *c_track, int i)
{
	char	*value;
	int		y;
	int		j;

	y = 0;
	j = 0;
	while (c_track->myenv[i][j] && c_track->myenv[i][j] != '=')
		j++;
	if (c_track->myenv[i][j] == '=')
		j++;
	else
		return (NULL);
	value = safe_malloc(sizeof(char) * ft_strlen(c_track->myenv[i]));
	while (c_track->myenv[i][j])
		value[y++] = c_track->myenv[i][j++];
	value[y] = '\0';
	return (value);
}

char	*return_value_env_if_exists(t_cmd_track *c_track, char *key)
{
	int		i;
	char	*key_env;

	i = 0;
	if (c_track->myenv)
	{
		while (c_track->myenv[i])
		{
			key_env = return_key(c_track->myenv[i]);
			if (ft_strcmp(key_env, key) == 0)
			{
				free(key_env);
				return (allocate_value(c_track, i));
			}
			free(key_env);
			i++;
		}
	}
	return (NULL);
}

void	ft_pwd(t_cmd_track *c_track, int fd)
{
	if (c_track->pwd == NULL)
	{
		custom_error("minishell: PWD not set\n", 1);
	}
	else
	{
		ft_putstr_fd(c_track->pwd, fd);
		write(fd, "\n", 1);
	}
}
