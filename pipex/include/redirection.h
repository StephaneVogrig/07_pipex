/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:33:33 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/26 20:02:45 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <fcntl.h>
# include "libft.h"
# include "pipex_const.h"

void	redirection(int fd_in, int fd_out);
void	close_pipe(int	*pipe_fd);
int		is_directory(char *path);

#endif