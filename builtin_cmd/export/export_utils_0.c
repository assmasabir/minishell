/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:54:37 by asabir            #+#    #+#             */
/*   Updated: 2024/09/29 09:46:05 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**create_copy(t_cmd_track *c_track, char **str, int *size)
{
	int		i;
	char	**cp;

	if (str)
	{
		while (str[*size])
			(*size)++;
	}
	if (*size == 0)
		return (create_mini_copy(c_track, size));
	cp = safe_malloc(sizeof(char *) * (*size + 1));
	i = 0;
	while (str[i])
	{
		cp[i] = ft_strdup(str[i]);
		i++;
	}
	cp[i] = NULL;
	return (cp);
}

void	get_index_of_small(t_cmd_track *c_track, char **cpy_env,
		int *index_of_small)
{
	int		count;
	int		i;
	char	*small;

	small = NULL;
	count = 0;
	i = 0;
	while (i < c_track->size_env)
	{
		count++;
		while (cpy_env[i] && cpy_env[i][0] == '0')
			i++;
		if (cpy_env[i] && count == 1)
		{
			*index_of_small = i;
			small = cpy_env[i++];
		}
		if (c_track->myenv[i] && ft_strcmp(small, cpy_env[i]) > 0
			&& cpy_env[i][0] != '0')
		{
			small = cpy_env[i];
			*index_of_small = i;
		}
		i++;
	}
}

void	loop(t_cmd_track *c_track, char **export, char **cpy_env)
{
	int	j;
	int	index_of_small;

	j = 0;
	index_of_small = 0;
	while (j < c_track->size_env && c_track->myenv)
	{
		get_index_of_small(c_track, cpy_env, &index_of_small);
		export[j] = ft_join("declare -x ", c_track->myenv[index_of_small]);
		free(cpy_env[index_of_small]);
		cpy_env[index_of_small] = ft_strdup("0");
		j++;
	}
}

void	add_var_if_not_exist(t_cmd_track *c_track, char *new_var, int added,
		int check)
{
	int	i;

	i = 0;
	while (i < c_track->size_env + added)
	{
		i++;
	}
	if (check == 0)
		c_track->myenv[i] = ft_strdup(new_var);
	else if (check == 3)
		c_track->myenv[i] = add_non_existing_append_var(new_var);
}

void	change_or_append_var_value(t_cmd_track *c_track, char *new_var,
		int check)
{
	int		i;
	char	*key_var;
	char	*key_env;

	i = 0;
	key_var = return_key(new_var);
	while (c_track->myenv[i])
	{
		key_env = return_key(c_track->myenv[i]);
		if (ft_strcmp(key_env, key_var) == 0)
		{
			free(key_env);
			break ;
		}
		i++;
		free(key_env);
	}
	if (check == 1)
	{
		change_value(c_track, new_var, i);
	}
	else if (check == 2)
		append_value(c_track, new_var, i);
	free(key_var);
}
