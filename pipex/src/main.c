/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:17:29 by stephane          #+#    #+#             */
/*   Updated: 2024/03/09 03:30:04 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **envp)
{
	char	*exe_path;
	char	**exe_argv;

	while (*cmd == ' ')
		cmd++;
	if (*cmd == '\0')
		exit(0);
	exe_argv = get_argv(cmd);
	if (!exe_argv)
	{
		perror("pipex: exec_cmd");
		exit(EXIT_FAILURE);
	}
	exe_path = cmd_path(exe_argv[0], envp);
	if (!exe_path)
	{
		ft_putstr_fd(*exe_argv, STDERR_FD);
		ft_putstr_fd(": command not found\n", STDERR_FD);
		ft_split_free(exe_argv);
		exit(127);
	}
	execve(exe_path, exe_argv, envp);
	perror("pipex");
	strtab_free(exe_argv);
	if (exe_path)
		free(exe_path);
	exit(EXIT_FAILURE);
}

void	close_pipe(int	*pipe_fd)
{
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
}

int	process_infile(char *file_path, char *cmd, int *pipe_fd, char **envp)
{
	int	fd;
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("process infile");
	if (pid != 0)
		return (pid);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FD);
		ft_putstr_fd(file_path, STDERR_FD);
		ft_putstr_fd(": ", STDERR_FD);
		perror("");
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

int	process_outfile(char *file_path, char *cmd, int *pipe_fd, char **envp)
{
	int	fd;
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("process outfile");
	if (pid != 0)
		return (pid);
	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FD);
		ft_putstr_fd(file_path, STDERR_FD);
		ft_putstr_fd(": ", STDERR_FD);
		perror("");
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

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid_in;
	pid_t	pid_out;
	int		wstatus;
	int		ret;

	wstatus = 0;
	ret = 0;
	if (argc != 5)
	{
		ft_putstr_fd("usage: ./pipex <file1> <cmd1> <cmd2> <file2>", STDERR_FD);
		return (1);
	}
	if (pipe(pipe_fd) == -1)
		return (error_perror("pipex: main"));
	pid_in = process_infile(argv[1], argv[2], pipe_fd, envp);
	pid_out = process_outfile(argv[4], argv[3], pipe_fd, envp);
	close_pipe(pipe_fd);
	if (pid_in > 0)
		waitpid(pid_in, &wstatus, 0);
	if (pid_out > 0)
		waitpid(pid_out, &wstatus, 0);
	if (WIFEXITED(wstatus))
		ret = WEXITSTATUS(wstatus);
	return (ret);
}
