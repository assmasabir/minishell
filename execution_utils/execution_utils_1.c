/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:17:09 by asabir            #+#    #+#             */
/*   Updated: 2024/09/26 10:20:01 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_exp(char *str, int fd)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			write(fd, &str[i], 1);
			check = 1;
			write(fd, "\"", 1);
			i++;
		}
		if (str[i])
			write(fd, &str[i], 1);
		else
			break ;
		i++;
	}
	if (check == 1)
		write(fd, "\"", 1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*cp;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	cp = safe_malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		cp[i] = str[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (-1);
}

char	*ft_strncpy(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (str1[i] && i < n)
	{
		str2[i] = str1[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
