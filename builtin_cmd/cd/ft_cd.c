/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:06:20 by asabir            #+#    #+#             */
/*   Updated: 2024/10/02 12:35:54 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(t_line_splited *head, t_cmd_track *c_track, int output)
{
	if (ft_strcmp(head->cmd[1], ".") == 0)
		return ;
	else if (head->cmd[1] == NULL)
		case_go_home(c_track, 0);
	else if (head->cmd[1] && head->cmd[2])
		custom_error("minishell: cd: too many arguments\n", 1);
	else if (ft_strcmp(head->cmd[1], "-") == 0)
		case_go_back(c_track, output);
	else if (ft_strcmp(head->cmd[1], "..") == 0)
		case_go_up(c_track);
	else if (ft_strcmp(head->cmd[1], "~") == 0)
		case_go_home(c_track, 1);
	else if (ft_strchr(head->cmd[1], '/') == 0)
		handle_absolute_paths(head, c_track);
	else
		directories_inside_current_directory(head, c_track);
}

void	case_go_back(t_cmd_track *c_track, int output)
{
	char	*old_env;
	char	*current_env;

	old_env = return_value_env_if_exists(c_track, "OLDPWD");
	if (old_env == NULL)
	{
		custom_error("minishell: cd: OLDPWD not set\n", 1);
		return ;
	}
	current_env = ft_strdup(c_track->pwd);
	if (access(old_env, X_OK) == -1)
		my_perror("cd", old_env, 1);
	else if (c_track->nb_pipes == 0)
	{
		if (chdir(old_env) == -1)
			my_perror("cd", old_env, 1);
		else
		{
			go_back_helper(c_track, current_env, old_env, output);
			return ;
		}
	}
	free_two_arrays(old_env, current_env);
}

void	case_go_up(t_cmd_track *c_track)
{
	char	*current_dir;
	char	*parent_dir;

	current_dir = ft_strdup(c_track->pwd);
	if (current_dir == NULL)
	{
		custom_error("error while getting the path of current directory\n", 1);
		return ;
	}
	parent_dir = parent_directory_path(current_dir);
	if (parent_dir == NULL)
	{
		free(current_dir);
		return ;
	}
	else if (access(parent_dir, X_OK) == -1)
	{
		my_perror("cd", parent_dir, 1);
		free(current_dir);
	}
	else if (c_track->nb_pipes == 0)
		change_directory(parent_dir, c_track, current_dir);
	else
		free(current_dir);
	free(parent_dir);
}

void	case_go_home(t_cmd_track *c_track, int tilde)
{
	char	*home_dir;
	char	*current_dir;

	current_dir = NULL;
	home_dir = return_value_env_if_exists(c_track, "HOME");
	if (home_dir && home_dir[0] == '\0')
	{
		free(home_dir);
		return ;
	}
	if (tilde == 1)
	{
		free(home_dir);
		home_dir = ft_strdup(c_track->home);
	}
	current_dir = ft_strdup(c_track->pwd);
	if (current_dir == NULL)
	{
		custom_error("error while getting the path of current directory\n", 1);
		return ;
	}
	case_go_home_helper(c_track, home_dir, current_dir);
}

void	handle_absolute_paths(t_line_splited *head, t_cmd_track *c_track)
{
	char	*current_dir;

	current_dir = NULL;
	current_dir = ft_strdup(c_track->pwd);
	if (current_dir == NULL)
	{
		custom_error("error while getting the path of current directory\n", 1);
		return ;
	}
	if (access(head->cmd[1], X_OK) == -1)
	{
		my_perror("cd", head->cmd[1], 1);
		free(current_dir);
	}
	else if (c_track->nb_pipes == 0)
		change_directory(head->cmd[1], c_track, current_dir);
	else if (c_track->nb_pipes != 0)
		free(current_dir);
}
