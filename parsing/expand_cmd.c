/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser </var/spool/mail/yasser>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:20:47 by yasser            #+#    #+#             */
/*   Updated: 2024/10/02 22:16:23 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	single_quotes_handler(char **str, char *new, int *i)
{
	new[*i] = **str;
	(*i)++;
	(*str)++;
	while (**str && **str != '\'')
	{
		new[*i] = **str;
		(*i)++;
		(*str)++;
	}
	new[*i] = **str;
	(*i)++;
	(*str)++;
}

void	double_quotes_handler(char **str, char **new, int *i, char **env)
{
	norminette3(str, i, new);
	while (**str && **str != '"')
	{
		if (**str == '$')
		{
			if (!is_alphanumeric(*(*str + 1)) && *(*str + 1) != '?')
			{
				norminette3(str, i, new);
				continue ;
			}
			new[0][*i] = '\0';
			found_dolar_sign_inside_dq(str, new, i, env);
		}
		else
		{
			norminette3(str, i, new);
		}
	}
	norminette3(str, i, new);
}

char	*expand_and_leave_quotes(char *str, char **env, int i, char *tmp)
{
	char	*new;

	new = safe_malloc(ft_strlen(str) + 1);
	tmp = str;
	while (*str)
	{
		if (*str == '\'')
			single_quotes_handler(&str, new, &i);
		else if (*str == '"')
			double_quotes_handler(&str, &new, &i, env);
		else if (*str == '$')
		{
			if (!is_alphanumeric(*(str + 1)) && *(str + 1) != '?')
			{
				new[i++] = *(str++);
				continue ;
			}
			new[i] = '\0';
			found_dolar_sign(&str, &new, &i, env);
		}
		else
			new[i++] = *(str++);
	}
	new[i] = '\0';
	return (free(tmp), new);
}

void	expand_cmd(char **cmd, char **env)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	tmp = NULL;
	while (cmd[i])
	{
		cmd[i] = expand_and_leave_quotes(cmd[i], env, j, tmp);
		i++;
	}
}
