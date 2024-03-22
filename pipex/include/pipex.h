/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:00:37 by stephane          #+#    #+#             */
/*   Updated: 2024/03/22 03:04:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include "libft.h"
# include "pipex_const.h"
# include "cmd_path.h"
# include "cmd_to_argv.h"
# include "redirection.h"
# include "str.h"
# include "token.h"

# define ERROR_USE "usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n"

void	exit_on_open_error(char *file_path, int pipe_fd[]);

#endif