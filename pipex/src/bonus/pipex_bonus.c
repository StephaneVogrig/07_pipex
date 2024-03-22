/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:15:04 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/22 02:48:37 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	*pipex_malloc(int size, char *error_msg)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror(error_msg);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

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
	if (path)
		free(path);
	exit(EXIT_FAILURE);
}

void	exit_pipex(char *msg, int *pids, int *fd, int *pipe)
{
	perror(msg);
	if (pids)
		free(pids);
	if (fd)
		close(*fd);
	if (pipe)
		close_pipe(pipe);
	exit(EXIT_FAILURE);
}

void	exit_pipex_open_error(char *file_path, int *fd, int *pipe)
{
	char	*error_msg;

	error_msg = pipex_strjoin("pipex: ", file_path);
	if (error_msg)
		perror(error_msg);
	if (fd)
		close(*fd);
	if (pipe)
		close_pipe(pipe);
	free(error_msg);
	exit(EXIT_FAILURE);
}
