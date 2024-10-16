/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:10:43 by yait-nas          #+#    #+#             */
/*   Updated: 2024/10/04 14:07:00 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_is_not_closed(char *line)
{
	while (*line)
	{
		if (*line == '"' || *line == '\'')
		{
			skip_until_find_match(&line, *line);
			if (!(*line))
				return (1);
		}
		line++;
	}
	return (0);
}

int	parsing(char *line, t_line_splited **head, char **env)
{
	*head = NULL;
	if (quote_is_not_closed(line))
	{
		ft_putstr_fd("syntax error\n", 2);
		g_exit_status_value = 2;
		return (-1);
	}
	replace_spaces_with_space(line);
	if (something_is_wrong(line))
	{
		ft_putstr_fd("syntax error\n", 2);
		g_exit_status_value = 2;
		return (-1);
	}
	set_up_for_execution(head, line);
	free(line);
	if (!(*head))
		return (1);
	if (expand_and_rm_quotes(head, env))
		return (free_everything(*head), -1);
	return (0);
}
