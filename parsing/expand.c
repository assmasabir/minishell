/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-nas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:25:30 by yait-nas          #+#    #+#             */
/*   Updated: 2024/10/04 14:09:41 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**join_matrices_ine_one_matrix(char ***tmp)
{
	char	**result;
	int		count;
	int		i;
	int		j;
	int		x;

	count = how_many_strings_in_triple_ptr(tmp);
	result = safe_malloc(sizeof(char *) * (count + 1));
	x = 0;
	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
			result[x++] = tmp[i][j++];
		free(tmp[i]);
		i++;
	}
	result[x] = NULL;
	free(tmp);
	return (result);
}

char	*clean_str(char *str)
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

void	last_but_not_least(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		matrix[i] = clean_str(matrix[i]);
		i++;
	}
}

char	**rm_quotes(char **cmd)
{
	char	**final_result;
	int		i;
	char	***tmp;
	char	**hold;

	tmp = safe_malloc(sizeof(char **) * (how_many_strings(cmd) + 1));
	i = 0;
	while (cmd[i])
	{
		hold = ft_split_with_white_spaces(cmd[i]);
		last_but_not_least(hold);
		tmp[i] = hold;
		i++;
	}
	tmp[i] = NULL;
	final_result = join_matrices_ine_one_matrix(tmp);
	return (free_matrix(cmd), final_result);
}

int	expand_and_rm_quotes(t_line_splited **head, char **env)
{
	t_line_splited	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (expand_redirection(tmp->redirection, env))
		{
			g_exit_status_value = 1;
			return (-1);
		}
		expand_cmd(tmp->cmd, env);
		tmp->cmd = rm_quotes(tmp->cmd);
		tmp = tmp->next;
	}
	return (0);
}
