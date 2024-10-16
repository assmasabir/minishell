/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser </var/spool/mail/yasser>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:21:40 by yasser            #+#    #+#             */
/*   Updated: 2024/09/10 09:21:41 by yasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_limiter_size(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] && tmp[i] != ' ' && tmp[i] != '<' && tmp[i] != '>')
	{
		if (tmp[i] == '"')
		{
			i++;
			while (tmp[i] && tmp[i] != '"')
				i++;
		}
		else if (tmp[i] == '\'')
		{
			i++;
			while (tmp[i] && tmp[i] != '\'')
				i++;
		}
		i++;
	}
	return (i);
}

int	how_many_strings(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	how_many_strings_in_triple_ptr(char ***ptr)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (ptr[i])
	{
		j = 0;
		while (ptr[i][j])
		{
			count++;
			j++;
		}
		i++;
	}
	return (count);
}
