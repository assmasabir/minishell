/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-nas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:17:12 by yait-nas          #+#    #+#             */
/*   Updated: 2024/09/10 11:13:56 by yasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display(t_line_splited *head)
{
	t_redirection	*tmp;
	int				i;
	char			**cmd;

	while (head)
	{
		printf("redirection:\n");
		tmp = head->redirection;
		while (tmp)
		{
			printf("redirection type: %d\n", tmp->redirection_type);
			printf("file/limiter: %s\n", tmp->file_limiter);
			tmp = tmp->next;
		}
		printf("cmd with options/args:\n");
		i = 0;
		cmd = head->cmd;
		while (cmd && cmd[i])
		{
			printf("%s\n", cmd[i]);
			i++;
		}
		head = head->next;
		printf("*******************************\n");
	}
}
