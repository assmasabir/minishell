/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 01:16:24 by asabir            #+#    #+#             */
/*   Updated: 2024/10/02 01:01:05 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_cmd_track *c_track, int fd)
{
	int	i;

	i = 0;
	if (c_track->myenv)
	{
		while (c_track->myenv[i])
		{
			if (ft_strchr(c_track->myenv[i], '=') == -1)
				i++;
			else
			{
				ft_putstr_fd(c_track->myenv[i], fd);
				write(fd, "\n", 1);
				i++;
			}
		}
	}
}
