/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:49:42 by asabir            #+#    #+#             */
/*   Updated: 2024/10/02 04:22:42 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_line_splited *head, t_cmd_track *c_track, int foutput)
{
	int		i;
	char	**export;

	i = 0;
	if (head->cmd[1] == NULL || head->cmd[1][0] == '#')
	{
		export = sort_env(c_track, c_track->myenv);
		while (export[i])
		{
			if (ft_strncmp(export[i], "declare -x _=",
					ft_strlen("declare -x _=")) == 0)
				i++;
			else
			{
				ft_putstr_exp(export[i], foutput);
				write(foutput, "\n", 1);
				i++;
			}
		}
		free_matrix(export);
	}
	else
		c_track->myenv = handle_variables(head, c_track);
}

char	**handle_variables(t_line_splited *head, t_cmd_track *c_track)
{
	int	index_of_next_var;
	int	j;

	c_track->count_added = 0;
	update_c_track(head, c_track, &index_of_next_var);
	j = 1;
	while (head->cmd[j])
	{
		if (check_if_valid(c_track, head->cmd[j], c_track->size_env,
				c_track->count_added) == 0)
			handle_valid_variable(c_track, head, &index_of_next_var, &j);
		else if (check_if_valid(c_track, head->cmd[j], c_track->size_env,
				c_track->count_added) == -1)
		{
			printf("minishell: export: '%s': not a valid identifier\n",
				head->cmd[j]);
			g_exit_status_value = 1;
		}
		else if (check_if_valid(c_track, head->cmd[j], c_track->size_env,
				c_track->count_added) == -3)
			break ;
		j++;
	}
	c_track->myenv[index_of_next_var] = NULL;
	return (c_track->myenv);
}

void	handle_valid_variable(t_cmd_track *c_track, t_line_splited *head,
		int *index_of_next_var, int *j)
{
	int	check;

	c_track->dup_keys_in_splited_line = 0;
	check = check_if_add_change_append(head, c_track, head->cmd[*j],
			*index_of_next_var);
	if (check == 0)
	{
		add_var_if_not_exist(c_track, head->cmd[*j], c_track->count_added,
			check);
		c_track->count_added++;
		(*index_of_next_var)++;
	}
	else if (check == 1)
		change_or_append_var_value(c_track, head->cmd[*j], check);
	else if (check == 2)
		change_or_append_var_value(c_track, head->cmd[*j], check);
	else if (check == 3)
	{
		add_var_if_not_exist(c_track, head->cmd[*j], c_track->count_added,
			check);
		c_track->count_added++;
		(*index_of_next_var)++;
	}
}

int	count_new_variables(t_cmd_track *c_track, t_line_splited *head, int size)
{
	int	i;
	int	nb;
	int	check;

	i = 1;
	nb = 0;
	while (head->cmd[i])
	{
		if (check_if_valid(c_track, head->cmd[i], size, 0) == 0)
		{
			check = check_if_add_change_append(head, c_track, head->cmd[i],
					size);
			if (check == 0 || check == 3)
				nb++;
		}
		i++;
	}
	return (nb - (c_track->dup_keys_in_splited_line / 2));
}

char	**sort_env(t_cmd_track *c_track, char **export)
{
	char	**cpy_env;

	c_track->size_env = 0;
	cpy_env = create_copy(c_track, c_track->myenv, &c_track->size_env);
	export = safe_malloc(sizeof(char *) * (c_track->size_env + 1));
	loop(c_track, export, cpy_env);
	export[c_track->size_env] = NULL;
	free_matrix(cpy_env);
	return (export);
}
