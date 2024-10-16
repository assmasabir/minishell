/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser </var/spool/mail/yasser>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:21:00 by yasser            #+#    #+#             */
/*   Updated: 2024/09/10 09:21:01 by yasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_matrix(char **line_splited)
{
	int	i;

	i = 0;
	if (!line_splited)
		return ;
	while (line_splited[i])
	{
		free(line_splited[i]);
		i++;
	}
	free(line_splited);
}
