/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:02:16 by stephane          #+#    #+#             */
/*   Updated: 2024/03/26 23:33:18 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	process_infile(char **cmd, int *pipe_out, char **envp, int *pids)
{
	int		fd;
	int		pid;
	char	*file_path;

	pid = fork();
	if (pid == 0)
	{
		close(pipe_out[READ]);
		free(pids);
		file_path = *(cmd - 1);
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
			exit_on_open_error(file_path, pipe_out[WRITE]);
		exec_cmd(fd, pipe_out[WRITE], *cmd, envp);
	}
	if (pid == -1)
		exit_pipex("pipex: process_infile: pipe", pids, pipe_out);
	return (pid);
}

int	process_heredoc(char **cmd, int *pipe_out, int *pids)
{
	t_list	*heredoc;
	int		pid;

	heredoc = get_heredoc(*(cmd - 1));
	if (!heredoc)
		exit_pipex("pipex: process_heredoc: get_heredoc", pids, pipe_out);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_out[READ]);
		free(pids);
		heredoc_write(heredoc, pipe_out[WRITE]);
		close(pipe_out[WRITE]);
		ft_lstclear(&heredoc, *free);
		exit(EXIT_SUCCESS);
	}
	ft_lstclear(&heredoc, *free);
	if (pid == -1)
		exit_pipex("pipex: process_heredoc: fork", pids, pipe_out);
	close(pipe_out[WRITE]);
	return (pid);
}

int	process_infile_hd(char **cmd, int *pipe_out, char **envp, int *pids)
{
	t_list	*heredoc;
	int		pid;
	int		pipe_in[2];

	if (pipe(pipe_in) == -1)
		exit_pipex("pipex: process_pipes: pipe", pids, pipe_out);
	heredoc = get_heredoc(*(cmd - 1));
	if (!heredoc)
		exit_pipex("pipex: process_heredoc: get_heredoc", pids, pipe_out);
	pid = fork();
	if (pid == 0)
	{
		free(pids);
		ft_lstclear(&heredoc, *free);
		close(pipe_in[WRITE]);
		close(pipe_out[READ]);
		exec_cmd(pipe_in[READ], pipe_out[WRITE], *cmd, envp);
	}
	ft_lstclear(&heredoc, *free);
	if (pid == -1)
		exit_pipex("pipex: process_heredoc: fork", pids, pipe_out);
	close(pipe_in[READ]);
	heredoc_write(heredoc, pipe_in[WRITE]);
	close(pipe_in[WRITE]);
	return (pid);
}

int	process_pipes(char **cmd, int *fd_in, char **envp, int *pids)
{
	int		pid;
	int		pipe_out[2];

	if (pipe(pipe_out) == -1)
	{
		perror("pipex: process_pipes: pipe");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		free(pids);
		close(pipe_out[READ]);
		exec_cmd(*fd_in, pipe_out[WRITE], *cmd, envp);
	}
	if (pid == -1)
		perror("pipex: process_pipes: fork");
	close(*fd_in);
	close(pipe_out[WRITE]);
	*fd_in = pipe_out[READ];
	return (pid);
}

int	process_outfile(char **cmd, int *fd_in, char **envp, int *pids)
{
	int		fd_out;
	int		pid;
	char	*file_path;

	pid = fork();
	if (pid == 0)
	{
		free(pids);
		file_path = *(cmd + 1);
		fd_out = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
			exit_on_open_error(file_path, *fd_in);
		exec_cmd(*fd_in, fd_out, *cmd, envp);
	}
	if (pid == -1)
		perror("pipex: process_outfile: fork");
	return (pid);
}

int	process_outfile_hd(char **cmd, int *fd_in, char **envp, int *pids)
{
	int		fd_out;
	int		pid;
	char	*file_path;

	pid = fork();
	if (pid == 0)
	{
		free(pids);
		file_path = *(cmd + 1);
		fd_out = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out == -1)
			exit_on_open_error(file_path, *fd_in);
		exec_cmd(*fd_in, fd_out, *cmd, envp);
	}
	if (pid == -1)
		perror("pipex: process_outfile: fork");
	return (pid);
}
