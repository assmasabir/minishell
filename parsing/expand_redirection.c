/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:21:21 by yasser            #+#    #+#             */
/*   Updated: 2024/10/04 17:58:44 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	last_but_not_least_redirection(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		matrix[i] = rm_quotes_redirection(matrix[i]);
		i++;
	}
}

void	here_doc_expand(t_redirection *node)
{
	char	*tmp;
	char	*new;
	int		i;

	i = 0;
	tmp = node->file_limiter;
	new = safe_malloc(ft_strlen(tmp) + 1);
	while (*tmp)
	{
		if (*tmp == '$')
		{
			if (is_alphanumeric(*(tmp + 1)))
				new[i++] = *tmp;
			tmp++;
		}
		else
			new[i++] = *(tmp++);
	}
	new[i] = '\0';
	tmp = node->file_limiter;
	node->file_limiter = rm_quotes_redirection_heredoc(new, node);
	free(new);
	free(tmp);
}

int	non_here_doc_expand(t_redirection *node, char **env)
{
	char	*tmp;
	char	*old;
	char	**hold;
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	old = ft_strdup(node->file_limiter);
	tmp = node->file_limiter;
	node->file_limiter = expand_and_leave_quotes(tmp, env, i, str);
	hold = ft_split_with_white_spaces(node->file_limiter);
	if (how_many_strings(hold) != 1)
	{
		printf("minishell: %s: ambiguous redirect\n", old);
		return (free_matrix(hold), free(old), -1);
	}
	last_but_not_least_redirection(hold);
	free(node->file_limiter);
	node->file_limiter = ft_strdup(*hold);
	return (free_matrix(hold), free(old), 0);
}

int	expand_redirection(t_redirection *head, char **env)
{
	while (head)
	{
		if (head->redirection_type == 2)
			here_doc_expand(head);
		else
		{
			if (non_here_doc_expand(head, env))
				return (-1);
		}
		head = head->next;
	}
	return (0);
}
