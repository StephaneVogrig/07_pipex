/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:17:29 by stephane          #+#    #+#             */
/*   Updated: 2024/03/20 07:36:56 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **envp)
{
	char	*path;
	char	**argv;

	while (*cmd == ' ')
		cmd++;
	path = cmd_path(cmd, envp);
	argv = cmd_to_argv(cmd);
	if (!argv)
		exit(EXIT_FAILURE);
	execve(path, argv, envp);
	perror("pipex");
	strtab_free(argv);
	free(path);
	exit(EXIT_FAILURE);
}

int	wait_process(pid_t pids[])
{
	int	wstatus;
	int	exit_code;

	wstatus = 0;
	exit_code = EXIT_FAILURE;
	if (pids[0] > 0)
		waitpid(pids[0], &wstatus, 0);
	if (pids[1] > 0)
		waitpid(pids[1], &wstatus, 0);
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	return (exit_code);
}

int	process_infile(char *file_path, char *cmd, int *pipe_fd, char **envp)
{
	int	fd;
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("pipex: process infile: fork");
	if (pid == 0)
	{
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
			exit_on_open_error(file_path, pipe_fd);
		close(pipe_fd[READ]);
		redirection(fd, pipe_fd[WRITE]);
		exec_cmd(cmd, envp);
	}
	return (pid);
}

int	process_outfile(char *file_path, char *cmd, int *pipe_fd, char **envp)
{
	int	fd;
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("pipex: process outfile: fork");
	if (pid == 0)
	{
		fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit_on_open_error(file_path, pipe_fd);
		close(pipe_fd[WRITE]);
		redirection(pipe_fd[READ], fd);
		exec_cmd(cmd, envp);
	}
	return (pid);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pids[2];

	if (argc != 5)
	{
		ft_putstr_fd(ERROR_USE, STDERR_FD);
		return (EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipex: main");
		return (EXIT_FAILURE);
	}
	pids[0] = process_infile(argv[1], argv[2], pipe_fd, envp);
	pids[1] = process_outfile(argv[4], argv[3], pipe_fd, envp);
	close_pipe(pipe_fd);
	return (wait_process(pids));
}
