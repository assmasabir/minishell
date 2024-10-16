/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser </var/spool/mail/yasser>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:20:38 by yasser            #+#    #+#             */
/*   Updated: 2024/09/23 04:33:27 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_and_blank(char **str, char c, char *dest, int *index)
{
	dest[*index] = **str;
	**str = ' ';
	(*str)++;
	(*index)++;
	while (**str && **str != c)
	{
		dest[*index] = **str;
		**str = ' ';
		(*index)++;
		(*str)++;
	}
}

char	*get_file_limiter(char *tmp)
{
	char	*file_limiter;
	int		i;

	i = 0;
	file_limiter = safe_malloc(file_limiter_size(tmp) + 1);
	while (*tmp && *tmp != ' ' && *tmp != '<' && *tmp != '>')
	{
		if (*tmp == '"' || *tmp == '\'')
			copy_and_blank(&tmp, *tmp, file_limiter, &i);
		file_limiter[i++] = *tmp;
		*tmp = ' ';
		tmp++;
	}
	file_limiter[i] = '\0';
	return (file_limiter);
}

void	fill_up_blank(t_line_splited *empty, int redirection_t, char *tmp)
{
	t_redirection	*redirection;

	if (*tmp == '<' || *tmp == '>')
	{
		*tmp = ' ';
		tmp++;
	}
	while (*tmp == ' ')
		tmp++;
	redirection = safe_malloc(sizeof(t_redirection));
	redirection->redirection_type = redirection_t;
	redirection->file_limiter = get_file_limiter(tmp);
	redirection->expand_in_here_doc_flag = 0;
	redirection->next = NULL;
	ft_lstadd_redirection(&(empty->redirection), redirection);
}

void	redirection_input(char *tmp, t_line_splited *empty_node)
{
	*(tmp++) = ' ';
	if (*tmp == '<')
		fill_up_blank(empty_node, 2, tmp);
	else
		fill_up_blank(empty_node, 1, tmp);
}

void	redirection_output(char *tmp, t_line_splited *empty_node)
{
	*(tmp++) = ' ';
	if (*tmp == '>')
		fill_up_blank(empty_node, 4, tmp);
	else
		fill_up_blank(empty_node, 3, tmp);
}
