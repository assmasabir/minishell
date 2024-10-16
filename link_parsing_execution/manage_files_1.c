/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:35:12 by asabir            #+#    #+#             */
/*   Updated: 2024/10/05 20:23:30 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_line(char *line, t_cmd_track *c_track, int flag)
{
	char	*tmp;
	char	*new;
	int		i;

	if (flag)
		return (line);
	new = safe_malloc(ft_strlen(line) + 1);
	i = 0;
	tmp = line;
	while (*tmp)
	{
		if (*tmp == '$')
		{
			if (!is_alphanumeric(*(tmp + 1)) && *(tmp + 1) != '?')
			{
				new[i++] = *(tmp++);
				continue ;
			}
			found_dolar_sign(&tmp, &new, &i, c_track->myenv);
		}
		else
			new[i++] = *(tmp++);
	}
	new[i] = '\0';
	return (free(line), new);
}

char	*create_file_name(void)
{
	int				fd;
	unsigned char	buffer[9];
	char			*result;
	int				chars_readen;
	int				i;

	i = 0;
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (NULL);
	chars_readen = read(fd, buffer, 8);
	if (chars_readen <= 0)
		return (close(fd), NULL);
	buffer[chars_readen] = '\0';
	while (buffer[i])
	{
		buffer[i] = buffer[i] % 26 + 97;
		i++;
	}
	result = ft_join("/tmp/minishell_heredoc_", (char *)buffer);
	close(fd);
	return (result);
}

int	update_exit_status_free_close(int pid, char *name_heredoc, int fd)
{
	int	status;

	waitpid(pid, &status, 0);
	if (status)
	{
		g_exit_status_value = 130;
		return (close(fd), free(name_heredoc), -1);
	}
	return (0);
}

void	loop_read_and_write(int fd, t_cmd_track *c_track,
		t_redirection *redirection)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, redirection->file_limiter) == 0 || line == NULL)
		{
			if (line == NULL)
			{
				ft_putstr_fd("minishell: warning: here-document ", 2);
				custom_error("delimited by end-of-file\n", 0);
			}
			free(line);
			break ;
		}
		line = expand_line(line, c_track, redirection->expand_in_here_doc_flag);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}

int	open_heredoc(t_cmd_track *c_track, t_redirection *redirection)
{
	int	fd;
	int	pid;

	c_track->name_heredoc = create_file_name();
	fd = open(c_track->name_heredoc, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
	{
		custom_error("minishell: error in opening file descriptor\n", 1);
		return (-1);
	}
	update_sigint(1);
	pid = fork();
	if (pid == -1)
		my_perror(NULL, NULL, 1);
	else if (!pid)
	{
		update_sigint(0);
		loop_read_and_write(fd, c_track, redirection);
		exit(0);
	}
	if (update_exit_status_free_close(pid, c_track->name_heredoc, fd))
		return (-1);
	return (fd);
}
