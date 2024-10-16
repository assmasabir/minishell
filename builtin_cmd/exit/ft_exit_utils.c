/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 04:42:29 by asabir            #+#    #+#             */
/*   Updated: 2024/10/01 21:20:37 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	crazy_case_has_2nd_arg(t_line_splited *head)
{
	unsigned int	status;

	if (exit_status_is_acceptable(head->cmd[2]))
	{
		if (head->cmd[3])
		{
			custom_error("exit\nminishell: exit: too many arguments\n", 1);
			return ;
		}
		printf("exit\n");
		status = ft_atou(head->cmd[2]) % 256;
		free_everything(head);
		exit(status);
	}
	else
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			head->cmd[2]);
		free_everything(head);
		exit(2);
	}
}

void	crazy_case(t_line_splited *head)
{
	if (head->cmd[2])
		crazy_case_has_2nd_arg(head);
	else
	{
		printf("exit\n");
		free_everything(head);
		exit(0);
	}
}

void	exit_has_args(t_line_splited *head)
{
	if (!ft_strcmp(head->cmd[1], "--"))
		crazy_case(head);
	else if (exit_status_is_acceptable(head->cmd[1]))
	{
		if (head->cmd[2])
		{
			custom_error("exit\nminishell: exit: too many arguments\n", 1);
			return ;
		}
		printf("exit\n");
		g_exit_status_value = ft_atou(head->cmd[1]) % 256;
		free_everything(head);
		exit(g_exit_status_value);
	}
	else
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			head->cmd[1]);
		free_everything(head);
		exit(2);
	}
}

void	crazy_case_but_there_is_more(t_line_splited *head)
{
	if (head->cmd[2])
	{
		if (exit_status_is_acceptable(head->cmd[2]))
		{
			if (head->cmd[3])
				custom_error("minishell: exit: too many arguments\n", 1);
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n",
				head->cmd[2]);
			g_exit_status_value = 2;
		}
	}
}

void	there_is_more(t_line_splited *head)
{
	if (head->cmd[1])
	{
		if (!ft_strcmp(head->cmd[1], "--"))
			crazy_case_but_there_is_more(head);
		else if (exit_status_is_acceptable(head->cmd[1]))
		{
			if (head->cmd[2])
				custom_error("minishell: exit: too many arguments\n", 1);
			else
				g_exit_status_value = ft_atou(head->cmd[1]) % 256;
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n",
				head->cmd[1]);
			g_exit_status_value = 2;
		}
	}
}
