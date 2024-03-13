/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:00:37 by stephane          #+#    #+#             */
/*   Updated: 2024/03/13 19:44:21 by svogrig          ###   ########.fr       */
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

# define ERROR_USE "usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n"

enum e_pipe {READ, WRITE};
enum e_bool {NO, YES};
enum e_free {NOT_BE_FREE, TO_BE_FREE};

char	*cmd_path(char *cmd, char **envp);
void	exec_cmd(char *cmd, char **envp);

int		len_next_token(char *str);
char	*str_to_token(char *str, char *token);
char	*malloc_next_token(char *str);

int		process_infile(char *file_path, char *cmd, int *pipe_fd, char **envp);
int		process_outfile(char *file_path, char *cmd, int *pipe_fd, char **envp);
void	close_pipe(int	*pipe_fd);

int		pipex_perror(char *msg);
int		pipex_error(char *msg);
void	cmd_not_found(char *cmd, t_bool to_be_free);

void	redirection(int fd_in, int fd_out);
int		is_directory(char *path);

void	exit_on_open_error(char *file_path, int	pipe_fd[]);

char	*pipex_strndup(char *str, int n, t_bool to_be_free);
char	*str_malloc(int size, const char *error_msg);
void	ft_strncpy(char *dest, char *src, int n);
char	*pipex_strjoin(char *str1, char *str2);

#endif