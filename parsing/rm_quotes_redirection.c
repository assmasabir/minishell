/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser </var/spool/mail/yasser>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:05:43 by yasser            #+#    #+#             */
/*   Updated: 2024/10/03 11:05:56 by yasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rm_quotes_redirection_heredoc(char *str, t_redirection *node)
{
	char	*new;
	char	*tmp;
	int		i;
	char	c;

	new = safe_malloc(ft_strlen(str) + 1);
	tmp = str;
	i = 0;
	while (*tmp)
	{
		if (*tmp == '"' || *tmp == '\'')
		{
			node->expand_in_here_doc_flag = 1;
			c = *tmp;
			tmp++;
			while (*tmp != c)
				new[i++] = *(tmp++);
			tmp++;
		}
		else
			new[i++] = *(tmp++);
	}
	new[i] = '\0';
	return (new);
}

char	*rm_quotes_redirection(char *str)
{
	char	*new;
	char	*tmp;
	int		i;

	new = safe_malloc(ft_strlen(str) + 1);
	tmp = str;
	i = 0;
	while (*tmp)
	{
		if (*tmp == -1)
			norminette2(-1, new, &i, &tmp);
		else if (*tmp == -2)
			norminette2(-2, new, &i, &tmp);
		else if (*tmp == '"' || *tmp == '\'')
			copy_whats_between_quotes(&tmp, *tmp, new, &i);
		else
			new[i++] = *(tmp++);
	}
	new[i] = '\0';
	return (free(str), new);
}
