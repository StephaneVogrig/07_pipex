/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:17:29 by stephane          #+#    #+#             */
/*   Updated: 2024/03/10 00:42:55 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_process(pid_t pids[])
{
	int	wstatus;
	int	exit_code;

	wstatus = 0;
	exit_code = EXIT_SUCCESS;
	if (pids[0] > 0)
		waitpid(pids[0], &wstatus, 0);
	if (pids[1] > 0)
		waitpid(pids[1], &wstatus, 0);
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pids[2];

	if (argc != 5)
	{
		ft_putstr_fd("usage: ", STDERR_FD);
		ft_putstr_fd("./pipex <file1> <cmd1> <cmd2> <file2>\n", STDERR_FD);
		return (EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipex: main");
		return (EXIT_FAILURE);
	}
	pids[0] = process_infile(argv[1], argv[2], pipe_fd, envp);
	pids[1] = process_outfile(argv[4], argv[3], pipe_fd, envp);
	close_pipe(pipe_fd);
	return (wait_process(pids));
}
