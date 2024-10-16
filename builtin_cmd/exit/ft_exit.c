/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 01:16:22 by asabir            #+#    #+#             */
/*   Updated: 2024/10/04 14:17:24 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_line_splited *head, t_cmd_track *c_track)
{
	if (c_track->nb_pipes == 0)
	{
		if (head->cmd[1])
			exit_has_args(head);
		else
		{
			printf("exit\n");
			free_everything(head);
			exit(0);
		}
	}
	else
		there_is_more(head);
}

int	exit_status_last_check(char *trimed)
{
	if (*trimed == '+')
	{
		if (ft_strcmp(trimed + 1, "9223372036854775807") > 0)
			return (0);
	}
	else if (*trimed == '-')
	{
		if (ft_strcmp(trimed + 1, "9223372036854775808") > 0)
			return (0);
	}
	else
	{
		if (ft_strcmp(trimed, "9223372036854775807") > 0)
			return (0);
	}
	return (1);
}

int	exit_status_is_acceptable(char *str)
{
	int		i;
	char	*trimed;

	i = 0;
	if (!str[i])
		return (0);
	trimed = ft_strtrim(str, " ");
	if (!trimed[i])
		return (free(trimed), 0);
	if (trimed[i] == '+' || trimed[i] == '-')
		i++;
	while (trimed[i])
	{
		if (trimed[i] < '0' || trimed[i] > '9')
			return (free(trimed), 0);
		i++;
	}
	if (!exit_status_last_check(trimed))
		return (free(trimed), 0);
	free(trimed);
	return (1);
}
