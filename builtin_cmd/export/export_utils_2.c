/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:55:46 by asabir            #+#    #+#             */
/*   Updated: 2024/10/02 11:41:39 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	escape_the_var_itself(t_line_splited *head, char *new_var, int *i,
		char **key_cmd)
{
	char	*tmp;

	tmp = *key_cmd;
	if (ft_strcmp(new_var, head->cmd[*i]) == 0)
	{
		(*i)++;
		if (head->cmd[*i])
		{
			free(tmp);
			*key_cmd = return_key(head->cmd[*i]);
		}
	}
}

void	change_value(t_cmd_track *c_track, char *new_var, int i)
{
	free(c_track->myenv[i]);
	c_track->myenv[i] = ft_strdup(new_var);
}

void	append_value(t_cmd_track *c_track, char *new_var, int i)
{
	char	*temp;

	temp = c_track->myenv[i];
	c_track->myenv[i] = ft_join(c_track->myenv[i], to_append(new_var));
	free(temp);
}

char	*to_append(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	i++;
	return (str + i);
}

char	*return_value(char *full_var)
{
	int	i;

	i = 0;
	while (full_var[i] != '\0' && full_var[i] != '=')
	{
		i++;
	}
	printf("%c\n", full_var[i]);
	if (full_var[i] == '\0')
		return (NULL);
	return (full_var + i);
}
