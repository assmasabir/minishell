/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:48:22 by asabir            #+#    #+#             */
/*   Updated: 2024/10/02 11:42:41 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// 0 es decir append
int	check_if_append(char *new_var)
{
	int	i;

	i = 0;
	while (new_var[i])
	{
		if (new_var[i] == '+' && new_var[i + 1] == '=')
			return (0);
		i++;
	}
	return (-1);
}

int	check_if_key_already_exists(t_cmd_track *c_track, char *new_var, int max)
{
	int		i;
	int		check;
	char	*keyenv;
	char	*keyvar;

	i = 0;
	check = 0;
	keyvar = return_key(new_var);
	while (i < max)
	{
		keyenv = return_key(c_track->myenv[i]);
		if (ft_strcmp(keyenv, keyvar) == 0)
		{
			free(keyenv);
			free(keyvar);
			return (1);
		}
		i++;
		free(keyenv);
	}
	free(keyvar);
	return (check);
}

// 0 es decir add
// 1 es decir change
// 2 es decir append
// 3 si escribimos una variable asi u+=value pero noexite antes
int	check_if_add_change_append(t_line_splited *head, t_cmd_track *c_track,
		char *new_var, int max)
{
	int	check;

	check = check_if_key_already_exists(c_track, new_var, max);
	if (check == 0 && check_if_append(new_var) != 0)
	{
		if (check_if_var_reapeated(head, new_var) == 1)
			c_track->dup_keys_in_splited_line++;
		return (0);
	}
	else if (check == 0 && check_if_append(new_var) == 0)
		return (3);
	else if (check == 1 && check_if_append(new_var) != 0)
		return (1);
	else if (check == 1 && check_if_append(new_var) == 0)
		return (2);
	return (-1);
}

int	check_characters(char *key)
{
	if (ft_strchr(key, '+') == 0 || ft_strchr(key, '-') == 0
		|| ft_strchr(key, '*') == 0 || ft_strchr(key, '@') == 0
		|| ft_strchr(key, '.') == 0 || ft_strchr(key, '{') == 0
		|| ft_strchr(key, '}') == 0 || ft_strchr(key, '[') == 0
		|| ft_strchr(key, ']') == 0 || ft_strchr(key, '%') == 0
		|| ft_strchr(key, '#') == 0)
	{
		return (1);
	}
	else
		return (0);
}

// si es valido returna 0 sino returna -1
int	check_if_valid(t_cmd_track *c_track, char *new_var, int size, int added)
{
	int		i;
	char	*key;

	i = 0;
	while (new_var[i] == ' ')
		i++;
	key = return_key_for_check_if_valid(new_var);
	if (new_var[i] == '#')
		return (free(key), -3);
	else if (check_if_should_update(c_track, new_var, size, added) == 1)
		return (free(key), -2);
	else if (check_characters(key) != 0)
		return (free(key), -1);
	else if ((new_var[i] < 'a' || new_var[i] > 'z') && (new_var[i] != '_'))
	{
		if (new_var[i] < 'A' || new_var[i] > 'Z')
			return (free(key), -1);
	}
	return (free(key), 0);
}
