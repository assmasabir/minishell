/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:38:34 by asabir            #+#    #+#             */
/*   Updated: 2024/10/02 11:40:03 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_if_var_reapeated(t_line_splited *head, char *new_var)
{
	int		i;
	char	*key_cmd;
	char	*key_new_var;

	i = 1;
	key_new_var = return_key(new_var);
	while (head->cmd[i])
	{
		key_cmd = return_key(head->cmd[i]);
		escape_the_var_itself(head, new_var, &i, &key_cmd);
		if (head->cmd[i] && ft_strcmp(key_cmd, key_new_var) == 0)
			return (free(key_cmd), free(key_new_var), 1);
		if (!head->cmd[i])
		{
			free(key_cmd);
			break ;
		}
		i++;
		free(key_cmd);
	}
	free(key_new_var);
	return (0);
}

int	check_if_should_update(t_cmd_track *c_track, char *new_var, int size,
		int added)
{
	int		i;
	char	*env_key;

	i = 0;
	if (ft_strchr(new_var, '=') == -1)
	{
		while (i < size + added)
		{
			env_key = return_key(c_track->myenv[i]);
			if (ft_strcmp(env_key, new_var) == 0)
			{
				free(env_key);
				return (1);
			}
			free(env_key);
			i++;
		}
	}
	return (0);
}

char	*return_key_for_check_if_valid(char *str)
{
	int		i;
	char	*key;

	i = 0;
	key = safe_malloc(ft_strlen(str) + 1);
	while (str[i] && str[i] != '=' && (str[i] != '+'))
	{
		key[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '+')
	{
		if (str[i + 1] != '=')
		{
			key[i] = str[i];
			i++;
		}
	}
	key[i] = '\0';
	return (key);
}
