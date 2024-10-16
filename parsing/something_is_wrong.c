/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   something_is_wrong.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser </var/spool/mail/yasser>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:21:09 by yasser            #+#    #+#             */
/*   Updated: 2024/09/10 09:21:10 by yasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_what_is_next(char *str)
{
	if (*str)
	{
		while (*str == ' ')
			str++;
		if (*str == '|' || *str == '\0')
			return (-1);
		else
			return (0);
	}
	return (-1);
}

int	with_pipes(char *line)
{
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line == '|')
			return (1);
		while (*line && *line != '|')
		{
			if ((*line == '"') | (*line == '\''))
				skip_until_find_match(&line, *line);
			line++;
		}
		if (*line)
		{
			if (check_what_is_next(++line))
				return (1);
		}
		if (*line && *line != '"' && *line != '\'')
			line++;
	}
	return (0);
}

int	redirection_handler(char **str, char c)
{
	(*str)++;
	if (**str == c)
		(*str)++;
	while (**str == ' ')
		(*str)++;
	if (**str == '<' || **str == '|' || **str == '>' || **str == ';'
		|| **str == '\0')
		return (1);
	return (0);
}

int	with_redirections(char *line)
{
	int	flag;

	while (*line)
	{
		flag = 1;
		if (*line == '"' || *line == '\'')
			skip_until_find_match(&line, *line);
		else if (*line == '<' || *line == '>')
		{
			flag = 0;
			if (redirection_handler(&line, *line))
				return (1);
		}
		if (flag)
			line++;
	}
	return (0);
}

int	something_is_wrong(char *line)
{
	if (with_pipes(line))
		return (1);
	if (with_redirections(line))
		return (1);
	return (0);
}
