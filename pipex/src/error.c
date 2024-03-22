/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:10:52 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/22 02:47:02 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_on_open_error(char *file_path, int pipe_fd[])
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
