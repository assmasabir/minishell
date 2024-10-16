/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-nas <yait-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:45:30 by yait-nas          #+#    #+#             */
/*   Updated: 2024/08/27 16:37:40 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(char *str)
{
	int	count;

	count = 1;
	while (*str)
	{
		while (*str && !is_space(*str))
		{
			if (*str == '"' || *str == '\'')
				skip_until_find_match(&str, *str);
			str++;
		}
		while (is_space(*str))
			str++;
		if (*str)
			count++;
	}
	return (count);
}

static char	*word(char *s, int i)
{
	char	*p;
	int		j;

	p = safe_malloc(i + 1);
	j = 0;
	while (j < i)
	{
		p[j++] = *s;
		s++;
	}
	p[j] = '\0';
	return (p);
}

static void	to_be_continued(char **strings, char *s)
{
	int	string_index;
	int	i;

	string_index = 0;
	while (*s)
	{
		if (!is_space(*s))
		{
			i = 0;
			while (s[i] && !is_space(s[i]))
			{
				if (s[i] == '"' || s[i] == '\'')
					skip_until_find_match_index_version(s, &i, s[i]);
				i++;
			}
			strings[string_index++] = word(s, i);
			s += i;
		}
		while (is_space(*s))
			s++;
	}
	strings[string_index] = NULL;
}

char	**ft_split_with_white_spaces(char *s)
{
	char	**strings;
	int		count;

	count = count_words(s);
	strings = safe_malloc(sizeof(char *) * (count + 1));
	to_be_continued(strings, s);
	return (strings);
}
