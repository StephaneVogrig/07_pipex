/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:17:29 by stephane          #+#    #+#             */
/*   Updated: 2024/03/03 13:38:10 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	exec_cmd(char *cmd, char **envp)
{
	char	*exe_path;
	char	**exe_argv;

	exe_argv = ft_split(cmd, ' ');
	exe_path = cmd_path(exe_argv, envp);
	if (!exe_path)
	{
		ft_putstr_fd(*exe_argv, STDERR_FD);
		ft_split_free(exe_argv);
		exit(error_msg(""));
	}
	execve(exe_path, exe_argv, envp);
	perror("");
	ft_split_free(exe_argv);
	if (exe_path)
		free(exe_path);
	exit(EXIT_FAILURE);	
}

void	close_pipe(int	*pipe_fd)
{
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
}

// ft_printf("process 1: %s > %s\n", file_path, cmd);
// ft_printf("exe_path:%s exe_argv:%s\n", exe_path, *exe_argv);
// ft_printf("exe_path:%s\n", exe_path);
int process_infile(char *file_path, char *cmd, int *pipe_fd, char **envp)
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
		close_pipe(pipe_fd);
		exit(error_perror(file_path));		
	}
	dup2(fd, STDIN_FD);
	dup2(pipe_fd[WRITE], STDOUT_FD);
	close(fd);
	close_pipe(pipe_fd);
	exec_cmd(cmd, envp);
	return (0);
}

// ft_printf("process 2: %s > %s\n", cmd, file_path);
int	process_outfile(char *file_path, char *cmd, int *pipe_fd, char **envp)
{
	int	fd;
	int	pid;
	
	pid = fork();
	if (pid == -1)
		perror("process outfile");
	if (pid != 0)
		return (pid);
	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		close_pipe(pipe_fd);
		exit(error_perror(file_path));		
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
	pid_t 	pid_in;
	pid_t 	pid_out;
	int		wstatus;

	if (argc != 5)
		return (error_msg("usage: ./pipex <file1> <cmd1> <cmd2> <file2>"));
	if (pipe(pipe_fd) == -1)
		return (error_perror("pipe"));
	pid_in = process_infile(argv[1], argv[2], pipe_fd, envp);
	pid_out = process_outfile(argv[4], argv[3], pipe_fd, envp);
	close_pipe(pipe_fd);
	if (pid_in > 0)
		waitpid(pid_in, &wstatus, 0);
	if (pid_out > 0)
		waitpid(pid_out, &wstatus, 0);
	return (0);
}
