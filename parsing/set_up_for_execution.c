/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_for_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 07:09:00 by yait-nas          #+#    #+#             */
/*   Updated: 2024/09/22 15:51:42 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_extract_redirections_cmd(t_line_splited *empty_node, char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (*tmp == '"' || *tmp == '\'')
			skip_until_find_match(&tmp, *tmp);
		else if (*tmp == '<')
			redirection_input(tmp, empty_node);
		else if (*tmp == '>')
			redirection_output(tmp, empty_node);
		tmp++;
	}
	empty_node->cmd = ft_split_quotes(str, ' ');
	free(str);
}

void	set_up_for_execution(t_line_splited **head, char *line)
{
	int				i;
	char			**line_splited;
	t_line_splited	*tmp;

	line_splited = ft_split_quotes(line, '|');
	i = 0;
	while (line_splited[i])
	{
		tmp = safe_malloc(sizeof(t_line_splited));
		tmp->redirection = NULL;
		tmp->cmd = NULL;
		tmp->next = NULL;
		ft_extract_redirections_cmd(tmp, ft_strdup(line_splited[i]));
		ft_lstadd_line_splited(head, tmp);
		i++;
	}
	free_matrix(line_splited);
}
