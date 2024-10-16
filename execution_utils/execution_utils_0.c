/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:55:39 by asabir            #+#    #+#             */
/*   Updated: 2024/09/29 10:44:29 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_size(t_line_splited *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

void	allocate_array(t_cmd_track *c_track)
{
	int	i;

	i = 0;
	c_track->fd = safe_malloc(sizeof(int *) * (c_track->nb_pipes));
	while (i < c_track->nb_pipes)
	{
		c_track->fd[i] = safe_malloc(sizeof(int) * 2);
		i++;
	}
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (-1);
	while (str1[i] && str2[i])
	{
		if (str1[i] == str2[i])
			i++;
		else
			break ;
	}
	return (str1[i] - str2[i]);
}
