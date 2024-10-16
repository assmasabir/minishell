/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:35:33 by asabir            #+#    #+#             */
/*   Updated: 2024/10/02 13:06:20 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	go_back_helper(t_cmd_track *c_track, char *current_env, char *old_env,
		int output)
{
	char	*var_and_value;

	var_and_value = ft_join("OLDPWD=", current_env);
	ft_putstr_fd(old_env, output);
	write(output, "\n", 1);
	change_variable(c_track, var_and_value);
	free(var_and_value);
	var_and_value = ft_join("PWD=", old_env);
	change_variable(c_track, var_and_value);
	update_pwd(c_track);
	free(var_and_value);
	free_two_arrays(old_env, current_env);
}

void	free_two_arrays(char *str1, char *str2)
{
	free(str1);
	free(str2);
}

void	case_go_home_helper(t_cmd_track *c_track, char *home_dir,
			char *current_dir)
{
	if (home_dir == NULL)
	{
		custom_error("minishell: cd: HOME not set\n", 1);
		free(current_dir);
	}
	else if (access(home_dir, X_OK) == -1)
	{
		my_perror("cd", home_dir, 1);
		free(home_dir);
		free(current_dir);
	}
	else if (c_track->nb_pipes == 0)
	{
		change_directory(home_dir, c_track, current_dir);
		free(home_dir);
	}
	else if (c_track->nb_pipes != 0)
	{
		free(home_dir);
		free(current_dir);
	}
}

char	*parent_directory_path(char *current_dir)
{
	char	*parent_dir;
	int		size_path;
	int		max;

	parent_dir = NULL;
	if (current_dir[0] == '/' && current_dir[1] == '\0')
		return (ft_strdup(current_dir));
	else
	{
		size_path = ft_strlen(current_dir);
		max = size_path - 1;
		while (current_dir[max] != '/')
			max--;
		parent_dir = safe_malloc(sizeof(char) * (max + 1));
		parent_dir = ft_strncpy(current_dir, parent_dir, max);
	}
	return (parent_dir);
}
