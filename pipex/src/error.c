/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:10:52 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/13 19:45:16 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_perror(char *msg)
{
	perror(msg);
	return (EXIT_FAILURE);
}

int	pipex_error(char *msg)
{
	ft_putstr_fd(msg, STDERR_FD);
	return (EXIT_FAILURE);
}

void	exit_on_open_error(char *file_path, int	pipe_fd[])
{
	char	*error_msg;

	error_msg = pipex_strjoin("pipex: ", file_path);
	if (error_msg)
	{
		perror(error_msg);
		free(error_msg);
	}
	close_pipe(pipe_fd);
	exit(EXIT_FAILURE);
}

void	cmd_not_found(char *cmd, t_bool to_be_free)
{
	char	*error_msg;

	error_msg = pipex_strjoin(cmd, ": command not found\n");
	if (error_msg)
	{
		ft_putstr_fd(error_msg, STDERR_FD);
		free(error_msg);
	}
	if (to_be_free)
		free(cmd);
	exit(127);
}
