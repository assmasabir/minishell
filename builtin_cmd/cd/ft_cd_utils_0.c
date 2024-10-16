/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:40:04 by asabir            #+#    #+#             */
/*   Updated: 2024/10/02 15:22:36 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	look_for_var_index(t_cmd_track *c_track,
			char *key_var, int *i)
{
	char	*key_env;

	while (c_track->myenv[*i])
	{
		key_env = return_key(c_track->myenv[*i]);
		if (ft_strcmp(key_env, key_var) == 0)
		{
			free(key_env);
			free(key_var);
			return (1);
		}
		(*i)++;
		free(key_env);
	}
	free(key_var);
	return (0);
}

void	change_variable(t_cmd_track *c_track, char *new_var)
{
	int		i;
	char	*key_var;
	int		deos_var_exists;

	i = 0;
	if (c_track->myenv)
	{
		key_var = return_key(new_var);
		deos_var_exists = look_for_var_index(c_track, key_var, &i);
		if (deos_var_exists == 1)
			change_value(c_track, new_var, i);
		else
			add_non_existing_var_implicitly(c_track, NULL, new_var);
	}
}

void	change_directory(char *dir_to_access, t_cmd_track *c_track,
		char *oldpwd)
{
	char	*var_and_value;

	if (chdir(dir_to_access) == -1)
	{
		my_perror("cd", dir_to_access, 1);
		free(oldpwd);
	}
	else
	{
		dir_to_access = NULL;
		dir_to_access = getcwd(dir_to_access, 0);
		var_and_value = ft_join("OLDPWD=", oldpwd);
		free(oldpwd);
		change_variable(c_track, var_and_value);
		free(var_and_value);
		var_and_value = ft_join("PWD=", dir_to_access);
		free(dir_to_access);
		change_variable(c_track, var_and_value);
		update_pwd(c_track);
		free(var_and_value);
	}
}

void	directories_inside_current_directory(t_line_splited *head,
		t_cmd_track *c_track)
{
	char	*current_dir;
	char	*tmp;
	char	*join;

	current_dir = ft_strdup(c_track->pwd);
	if (current_dir == NULL)
	{
		custom_error("error while getting the path of current directory\n", 1);
		return ;
	}
	tmp = ft_join(current_dir, "/");
	join = ft_join(tmp, head->cmd[1]);
	if (access(join, X_OK) == -1)
	{
		my_perror("cd", head->cmd[1], 1);
		free(current_dir);
	}
	else if (c_track->nb_pipes == 0)
	{
		(void)change_directory(join, c_track, current_dir);
	}
	else
		free(current_dir);
	free_two_arrays(tmp, join);
}

void	add_non_existing_var_implicitly(t_cmd_track *c_track,
		t_line_splited *head, char *new_var)
{
	int	index_of_next_var;

	index_of_next_var = create_new_environ(c_track, head, 1);
	c_track->myenv[index_of_next_var] = ft_strdup(new_var);
	c_track->myenv[index_of_next_var + 1] = NULL;
}
