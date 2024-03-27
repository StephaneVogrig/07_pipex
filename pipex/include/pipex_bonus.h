/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:21:26 by stephane          #+#    #+#             */
/*   Updated: 2024/03/27 17:20:05 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/wait.h>
# include <sys/types.h>
# include "pipex_const.h"
# include "cmd_to_argv.h"
# include "exit.h"
# include "exec_cmd.h"

# define ERROR_USE_BONUS "\
usage: \n\
./pipex <file1> <cmd1> ... <cmdn> <file2>\n\
./pipex here_doc limiter <cmd1> ... <cmdn> <file>\n\
"

# define ERROR_HDOC "pipex: warning: here-document delimited by end-of-file"

/* pipex bonus -------------------------------------------------------------*/

void	*pipex_malloc(int size, char *error_msg);
void	exit_pipex(char *msg, int *pids, int *pipe);

/* heredoc bonus -------------------------------------------------------------*/

void	heredoc_write(t_list *hd_lst, int fd);
t_list	*get_heredoc(char *limiter);

/* process bonus -------------------------------------------------------------*/

int		process_infile(char **cmd, int *pipe_out, char **envp, int *pids);
int		process_heredoc(char *limiter, int *pipe_out, int *pids);
int		process_infile_hd(char **cmd, int *pipe_fd, char **envp, int *pids);
int		process_pipes(char **cmd, int *fd_in, char **envp, int *pids);
int		process_outfile(char **cmd, int *fd_in, char **envp, int *pids);
int		process_outfile_hd(char **cmd, int *fd_in, char **envp, int *pids);

#endif