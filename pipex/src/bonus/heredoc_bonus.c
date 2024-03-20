/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:09:17 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/20 07:56:05 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_bool	gen_path(char *path)
{
	int	fd; 

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
	{
		perror("pipex: gen_path: open");
		return (ERROR);
	}
	if (read(fd, path, 17) < 0)
	{
		close(fd);
		perror("pipex: gen_path: read");
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

t_bool	temp_path(char *path)
{
	ft_memcpy(path, "/temp/pipex_", 12);
	path[29] = '\0';
	if (!gen_path(path + 12))
		return (ERROR);
	while (access(path, F_OK) == 0)
		gen_path(path);
	return (SUCCESS);
}

int	get_heredoc(char *limiter, char *path)
{
	char	*line;
	int		fd;

	if (!temp_path(path))
		return (-1);
ft_putstr_fd(path, 2);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	unlink(path);
	line = get_next_line(fd);
	while (line && ft_strcmp(line, limiter) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (fd);
}
