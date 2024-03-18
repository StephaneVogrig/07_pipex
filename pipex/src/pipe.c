/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_outfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:42:11 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/13 02:57:00 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int	*pipe_fd)
{
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
}