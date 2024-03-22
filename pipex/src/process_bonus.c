/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:02:16 by stephane          #+#    #+#             */
/*   Updated: 2024/03/21 08:12:04 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	process_infile(char **cmd, int *pipe_out, char **envp, int *pids)
{
	int		fd;
	int		pid;
	char	*file_path;

	pid = fork();
	if (pid == -1)
		exit_pipex("pipex: process_infile: pipe", pids, NULL, pipe_out);
	if (pid == 0)
	{
		free(pids);
		file_path = *(cmd - 1);
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
			exit_pipex_open_error(file_path, NULL, pipe_out);
		close(pipe_out[READ]);
		redirection(fd, pipe_out[WRITE]);
		exec_cmd(*cmd, envp);
	}
	return (pid);
}

int	process_heredoc(char **cmd, int *pipe_out, char **envp, int *pids)
{
	t_list	*hd_lst;
	int		pid;
	int		pipe_in[2];

	if (pipe(pipe_in) == -1)
		exit_pipex("pipex: process_pipes: pipe", pids, NULL, pipe_out);
	hd_lst = get_heredoc(*(cmd - 1));
	if (!hd_lst)
		exit_pipex("pipex: process_heredoc: get_heredoc", pids, NULL, pipe_out);
	pid = fork();
	if (pid == -1)
		exit_pipex("pipex: process_heredoc: fork", pids, NULL, pipe_out);
	if (pid == 0)
	{
		free(pids);
		close(pipe_in[WRITE]);
		close(pipe_out[READ]);
		redirection(pipe_in[READ], pipe_out[WRITE]);
		exec_cmd(*cmd, envp);
	}
	close(pipe_in[READ]);
	heredoc_write(hd_lst, pipe_in[WRITE]);
	close(pipe_in[WRITE]);
	ft_lstclear(&hd_lst, *free);
	return (pid);
}

int	process_pipes(char **cmd, int *fd_in, char **envp, int *pids)
{
	int		pid;
	int		pipe_out[2];

	if (pipe(pipe_out) == -1)
		exit_pipex("pipex: process_pipes: pipe", pids, fd_in, NULL);
	pid = fork();
	if (pid == -1)
		exit_pipex("pipex: process_pipes: fork", pids, NULL, pipe_out);
	if (pid == 0)
	{
		free(pids);
		close(pipe_out[READ]);
		redirection(*fd_in, pipe_out[WRITE]);
		exec_cmd(*cmd, envp);
	}
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
	if (pid == -1)
		exit_pipex("pipex: process_outfile: fork", pids, fd_in, NULL);
	if (pid == 0)
	{
		free(pids);
		file_path = *(cmd + 1);
		fd_out = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
			exit_pipex_open_error(file_path, fd_in, NULL);
		redirection(*fd_in, fd_out);
		exec_cmd(*cmd, envp);
	}
	close (*fd_in);
	return (pid);
}
