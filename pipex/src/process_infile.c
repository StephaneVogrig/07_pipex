/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_infile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:41:38 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/10 00:41:54 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	process_infile(char *file_path, char *cmd, int *pipe_fd, char **envp)
{
	int	fd;
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("pipex: process infile");
	if (pid != 0)
		return (pid);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FD);
		perror(file_path);
		close_pipe(pipe_fd);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FD);
	dup2(pipe_fd[WRITE], STDOUT_FD);
	close(fd);
	close_pipe(pipe_fd);
	exec_cmd(cmd, envp);
	return (0);
}
