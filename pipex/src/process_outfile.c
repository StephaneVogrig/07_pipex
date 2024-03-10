/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_outfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:42:11 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/10 00:44:06 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int	*pipe_fd)
{
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
}

int	process_outfile(char *file_path, char *cmd, int *pipe_fd, char **envp)
{
	int	fd;
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("pipe: process outfile");
	if (pid != 0)
		return (pid);
	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FD);
		perror(file_path);
		close_pipe(pipe_fd);
		exit(EXIT_FAILURE);
	}
	dup2(pipe_fd[READ], STDIN_FD);
	dup2(fd, STDOUT_FD);
	close(fd);
	close_pipe(pipe_fd);
	exec_cmd(cmd, envp);
	return (0);
}
