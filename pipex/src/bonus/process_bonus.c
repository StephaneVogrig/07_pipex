/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:02:16 by stephane          #+#    #+#             */
/*   Updated: 2024/03/17 16:58:28 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

int	process_inter(char *cmd, int *pipe_in, char **envp)
{
	int		pid;
	int		pipe_out[2];
	
	if (pipe(pipe_out) == -1)
		return (pipex_perror("pipex: process_inter: pipe"));
	pid = fork();
	if (pid == -1)
		perror("pipex: process inter: fork");
	if (pid == 0)
	{
		close(pipe_in[WRITE]);
		close(pipe_out[READ]);
		redirection(pipe_in[READ], pipe_out[WRITE]);
		exec_cmd(cmd, envp);
	}
	close_pipe(pipe_in);
	pipe_in[READ] = pipe_out[READ];
	pipe_in[WRITE] = pipe_out[WRITE];
	return (pid);
}

