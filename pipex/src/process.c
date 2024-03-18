/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:41:38 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/17 19:43:18 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

int	process_infile(char *file_path, char *cmd, int *pipe_fd, char **envp)
{
	int		fd;
	int		pid;
	

	pid = fork();
	if (pid == -1)
		perror("pipex: process infile: fork");
	if (pid != 0)
		return (pid);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		exit_on_open_error(file_path, pipe_fd);
	close(pipe_fd[READ]);
	redirection(fd, pipe_fd[WRITE]);
	exec_cmd(cmd, envp);
	return (0);
}

int	process_outfile(char *file_path, char *cmd, int *pipe_fd, char **envp)
{
	int	fd;
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("pipex: process outfile: fork");
	if (pid != 0)
		return (pid);
	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_on_open_error(file_path, pipe_fd);
	close(pipe_fd[WRITE]);
	redirection(pipe_fd[READ], fd);
	exec_cmd(cmd, envp);
	return (0);
}