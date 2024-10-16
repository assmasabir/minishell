/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 01:16:16 by asabir            #+#    #+#             */
/*   Updated: 2024/10/01 21:31:37 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_key_exists(t_line_splited *head, t_cmd_track *c_track, int *i,
		int z)
{
	char	*key_env;

	while (c_track->myenv[*i])
	{
		key_env = return_key(c_track->myenv[*i]);
		if (ft_strcmp(key_env, head->cmd[z]) == 0)
		{
			free(key_env);
			return (1);
		}
		free(key_env);
		(*i)++;
	}
	return (0);
}

void	reset_env(t_cmd_track *c_track, int j)
{
	free(c_track->myenv[j]);
	while (c_track->myenv[j + 1])
	{
		c_track->myenv[j] = c_track->myenv[j + 1];
		j++;
	}
	c_track->myenv[j] = NULL;
}

void	ft_unset(t_line_splited *head, t_cmd_track *c_track)
{
	int	i;
	int	j;
	int	z;

	z = 1;
	if (c_track->nb_pipes != 0)
		return ;
	while (head->cmd[z])
	{
		i = 0;
		j = 0;
		if (check_if_key_exists(head, c_track, &i, z) == 1)
		{
			while (c_track->myenv[j])
			{
				if (i == j)
				{
					reset_env(c_track, j);
					break ;
				}
				j++;
			}
		}
		z++;
	}
}
