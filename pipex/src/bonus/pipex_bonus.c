/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:15:04 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/26 22:05:29 by svogrig          ###   ########.fr       */
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

void	exit_pipex(char *msg, int *pids, int *pipe)
{
	perror(msg);
	free(pids);
	if (pipe)
		close_pipe(pipe);
	exit(EXIT_FAILURE);
}
