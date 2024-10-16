/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:25:36 by asabir            #+#    #+#             */
/*   Updated: 2024/10/01 19:36:12 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_exit_error_based_on_errno(void)
{
	if (errno == ENOENT)
		g_exit_status_value = 127;
	else if (errno == EACCES || errno == ENOEXEC || errno == ETXTBSY)
		g_exit_status_value = 126;
	else
		g_exit_status_value = 1;
}

void	my_perror(char *function_name, char *file_name, int exit_status)
{
	ft_putstr_fd("minishell: ", 2);
	if (function_name)
	{
		ft_putstr_fd(function_name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(file_name, 2);
	perror(" ");
	if (exit_status != 0)
		g_exit_status_value = exit_status;
	else
		update_exit_error_based_on_errno();
}

void	custom_error(char *error_message, int exit_status)
{
	ft_putstr_fd(error_message, 2);
	g_exit_status_value = exit_status;
}

void	free_all(t_cmd_track *c_track)
{
	free(c_track->pwd);
	free(c_track->home);
	free(c_track);
}
