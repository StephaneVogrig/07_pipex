/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:36:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/20 03:35:47 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

void	redirection(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FD);
	dup2(fd_out, STDOUT_FD);
	close(fd_in);
	close(fd_out);
}

void	close_pipe(int	*pipe_fd)
{
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
}

int	is_directory(char *path)
{
	int fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
		close(fd);
	return(fd >= 0);
}
