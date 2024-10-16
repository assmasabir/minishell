/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:00:00 by asabir            #+#    #+#             */
/*   Updated: 2024/10/02 11:41:29 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_c_track(t_line_splited *head, t_cmd_track *c_track, int *i)
{
	c_track->size_env = size_env(c_track->myenv);
	*i = create_new_environ(c_track, head, 0);
}

char	*return_key(char *str)
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
	key[i] = '\0';
	return (key);
}

int	return_size_env(t_cmd_track *c_track)
{
	int	i;

	i = 0;
	while (c_track->myenv[i])
		i++;
	return (i);
}

int	create_new_environ(t_cmd_track *c_track, t_line_splited *head, int nb)
{
	int		i;
	char	**copy;
	int		size;

	i = 0;
	size = 0;
	if (c_track->myenv)
	{
		while (c_track->myenv[size])
			size++;
	}
	if (nb == 0)
		nb = count_new_variables(c_track, head, size);
	copy = create_copy(c_track, c_track->myenv, &size);
	free_matrix(c_track->myenv);
	c_track->myenv = safe_malloc(sizeof(char *) * (nb + size + 1));
	while (copy[i])
	{
		c_track->myenv[i] = copy[i];
		i++;
	}
	free(copy);
	return (i);
}

char	*add_non_existing_append_var(char *new_var)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = safe_malloc(ft_strlen(new_var));
	while (new_var[i])
	{
		if (new_var[i] == '+')
			i++;
		str[j] = new_var[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
