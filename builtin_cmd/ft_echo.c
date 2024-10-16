/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:14:26 by asabir            #+#    #+#             */
/*   Updated: 2024/10/02 02:27:40 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_dash_n_valid(t_line_splited *head)
{
	int	i;
	int	j;

	j = 1;
	while (head->cmd[j] && ft_strncmp(head->cmd[j], "-n", 2) == 0)
	{
		i = 1;
		while (head->cmd[j][i] != '\0')
		{
			if (head->cmd[j][i] != 'n')
				return (j);
			i++;
		}
		j++;
	}
	return (j);
}

void	case_dash_n(t_line_splited *head, int fd, int index)
{
	if (head->cmd[index] != NULL)
	{
		while (head->cmd[index])
		{
			ft_putstr_fd(head->cmd[index], fd);
			if (head->cmd[index + 1])
				write(fd, " ", 1);
			index++;
		}
	}
}

void	ft_echo(t_line_splited *head, int fd)
{
	int	i;
	int	index;

	i = 1;
	index = check_if_dash_n_valid(head);
	if (head->cmd[1] == NULL)
		write(fd, "\n", 1);
	else if (index > 1)
		case_dash_n(head, fd, index);
	else
	{
		while (head->cmd[i])
		{
			ft_putstr_fd(head->cmd[i], fd);
			if (head->cmd[i + 1])
				write(fd, " ", 1);
			i++;
		}
		write(fd, "\n", 1);
	}
}
