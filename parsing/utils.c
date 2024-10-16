/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-nas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:29:40 by yait-nas          #+#    #+#             */
/*   Updated: 2024/09/10 17:26:06 by yasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_until_find_match(char **str, char c)
{
	(*str)++;
	while (**str && **str != c)
		(*str)++;
}

void	skip_until_find_match_index_version(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
}

void	copy_until_find_match(char **str, char c, char *dest, int *index)
{
	dest[*index] = **str;
	(*index)++;
	(*str)++;
	while (**str && **str != c)
	{
		dest[*index] = **str;
		(*index)++;
		(*str)++;
	}
}

void	replace_spaces_with_space(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			skip_until_find_match(&str, *str);
		else if (*str >= 9 && *str <= 13)
			*str = ' ';
		str++;
	}
}

void	*safe_malloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
	{
		printf("dynamic allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	return (result);
}
