/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:00:37 by stephane          #+#    #+#             */
/*   Updated: 2024/03/10 01:31:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft.h"

# define READ 0
# define WRITE 1

char	*cmd_path(char *cmd, char **envp);
void	exec_cmd(char *cmd, char **envp);

int		size_next_token(char *str);
char	*str_to_token(char *str, char *token);
char	*malloc_next_token(char *str);

int		process_infile(char *file_path, char *cmd, int *pipe_fd, char **envp);
int		process_outfile(char *file_path, char *cmd, int *pipe_fd, char **envp);
void	close_pipe(int	*pipe_fd);

#endif