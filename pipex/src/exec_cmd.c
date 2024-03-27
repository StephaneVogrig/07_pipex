/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:47 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/27 16:45:22 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

void	exec_cmd(int fd_in, int fd_out, char *cmd, char **envp)
{
	char	*path;
	char	**argv;

	dup2(fd_in, STDIN_FD);
	close(fd_in);
	dup2(fd_out, STDOUT_FD);
	close(fd_out);
	while (*cmd == ' ')
		cmd++;
	argv = cmd_to_argv(cmd);
	if (!argv)
		exit(EXIT_FAILURE);
	path = cmd_path(argv, envp);
	if (!path)
	{
		strtab_free(argv);
		exit(EXIT_FAILURE);
	}
	execve(path, argv, envp);
	perror("pipex");
	strtab_free(argv);
	free(path);
	exit(EXIT_FAILURE);
}
