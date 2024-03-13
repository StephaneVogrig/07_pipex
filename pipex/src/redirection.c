/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:36:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/13 01:45:31 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirection(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FD);
	dup2(fd_out, STDOUT_FD);
	close(fd_in);
	close(fd_out);
}
