/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:13:09 by asabir            #+#    #+#             */
/*   Updated: 2024/10/03 23:50:44 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status_value = 0;

int	main(int argc, char **argv, char **env)
{
	char				*line;
	t_cmd_track			*c_track;

	c_track = safe_malloc(sizeof(t_cmd_track));
	set_required_variables(c_track, env);
	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			set_signals();
			line = readline("\033[0;33mMINISHELL : \033[0m");
			if (!line)
			{
				printf("exit\n");
				break ;
			}
			add_history(line);
			minishell(c_track, line);
		}
		free_required_variables(c_track);
		rl_clear_history();
	}
	else
		write(2, "No arguments required!\n", 23);
}
