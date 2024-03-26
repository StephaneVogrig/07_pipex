/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:56:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/26 23:32:59 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	exit_on_cmd_not_found(char *cmd, t_bool to_be_free)
{
	fd_printf(STDERR_FD, "%s: command not found\n", cmd);
	if (to_be_free)
		free(cmd);
	exit(127);
}

void	exit_on_open_error(char *file_path, int fd)
{
	fd_printf(STDERR_FD, "pipex: %s: %s\n", file_path, strerror(errno));
	close(fd);
	exit(EXIT_FAILURE);
}

void	exit_perror(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
