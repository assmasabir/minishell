/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elite <elite@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 01:16:06 by asabir            #+#    #+#             */
/*   Updated: 2024/08/17 15:24:44 by elite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/home/elite/Desktop/miinishell/minishell.h"

char	*free_and_join(char **reserve, char *buff)
{
	char	*temp;

	temp = ft_join(*reserve, buff);
	free(*reserve);
	if (temp == NULL)
		return (NULL);
	return (temp);
}


char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
