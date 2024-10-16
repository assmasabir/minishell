/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:19:18 by asabir            #+#    #+#             */
/*   Updated: 2024/10/04 18:57:16 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (i < n && str1[i] && str2[i])
	{
		if (str1[i] == str2[i])
		{
			i++;
			if (i == n)
				return (0);
		}
		else
			break ;
	}
	return (str1[i] - str2[i]);
}

int	count_paths(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	**ft_split_helper(char *str, char **to_return, char c, int nb_paths)
{
	int	i;
	int	size;
	int	n;

	i = 0;
	size = 0;
	while (i < nb_paths)
	{
		size = 0;
		n = 0;
		while (str[size] != c && str[size])
			size++;
		to_return[i] = safe_malloc((size + 1));
		while (n < size)
		{
			to_return[i][n++] = *str;
			str++;
		}
		str++;
		to_return[i++][n] = '\0';
	}
	to_return[i] = NULL;
	return (to_return);
}

char	**ft_split(char *str, char c)
{
	int		nb_paths;
	char	**to_return ;

	if (str == NULL)
		return (NULL);
	nb_paths = count_paths(str, c);
	to_return = safe_malloc(sizeof(char *) * (nb_paths + 1));
	to_return = ft_split_helper(str, to_return, c, nb_paths);
	return (to_return);
}

char	*ft_join(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*to_join;

	i = 0;
	j = 0;
	to_join = safe_malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	while (str1[i])
	{
		to_join[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		to_join[i] = str2[j];
		i++;
		j++;
	}
	to_join[i] = '\0';
	return (to_join);
}
