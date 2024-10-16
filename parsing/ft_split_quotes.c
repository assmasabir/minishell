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

static int	count_words(char *str, char c)
{
	int	count;

	count = 1;
	while (*str)
	{
		while (*str && *str != c)
		{
			if (*str == '"' || *str == '\'')
				skip_until_find_match(&str, *str);
			str++;
		}
		while (*str == c)
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

static void	to_be_continued(char **strings, char *s, char c)
{
	int	string_index;
	int	i;

	string_index = 0;
	while (*s)
	{
		if (*s != c)
		{
			i = 0;
			while (s[i] && s[i] != c)
			{
				if (s[i] == '"' || s[i] == '\'')
					skip_until_find_match_index_version(s, &i, s[i]);
				i++;
			}
			strings[string_index++] = word(s, i);
			s += i;
		}
		while (*s == c)
			s++;
	}
	strings[string_index] = NULL;
}

char	**ft_split_quotes(char *s, char c)
{
	char	**strings;
	int		count;

	count = count_words(s, c);
	strings = safe_malloc(sizeof(char *) * (count + 1));
	to_be_continued(strings, s, c);
	return (strings);
}
