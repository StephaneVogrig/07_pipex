/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:56:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/28 22:22:47 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	exit_on_is_directory(char *path, char *to_free, char **argv)
{
	fd_printf(STDERR_FD, "pipex: %s: is a directory\n", *path);
	strtab_free(argv);
	if (to_free)
		free(to_free);
	exit(126);
}

void	exit_on_acces_denied(char *path, char *to_free, char **argv)
{
	fd_printf(STDERR_FD, "pipex: %s: %s\n", *path, strerror(errno));
	strtab_free(argv);
	if (to_free)
		free(to_free);
	exit(127);
}

void	exit_on_cmd_not_found(char **argv)
{
	fd_printf(STDERR_FD, "%s: command not found\n", *argv);
	strtab_free(argv);
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
