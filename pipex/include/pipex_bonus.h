/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:21:26 by stephane          #+#    #+#             */
/*   Updated: 2024/03/20 05:30:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H


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

# define ERROR_USE_BONUS "\
usage: \n\
./pipex <file1> <cmd1> ... <cmdn> <file2>\n\
./pipex here_doc limiter <cmd1> ... <cmdn> <file>\n\
"

/* pipex bonus -------------------------------------------------------------*/

void	*pipex_malloc(int size, char *error_msg);
void	exec_cmd(char *cmd, char **envp, int *pids);
void	exit_pipex(char *msg, int *pids, int *fd, int *pipe);
void	exit_pipex_open_error(char *file_path, int *pids, int *fd, int *pipe);

/* heredoc bonus -------------------------------------------------------------*/

int		get_heredoc(char *limiter, char *path);

/* process bonus -------------------------------------------------------------*/

int		process_infile(char **cmd, int *pipe_out, char **envp, int *pids);
int		process_heredoc(char **cmd, int *pipe_fd, char **envp, int *pids);
int		process_pipes(char **cmd, int *fd_in, char **envp, int *pids);
int		process_outfile(char **cmd, int *fd_in, char **envp, int *pids);

#endif