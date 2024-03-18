/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:35:58 by stephane          #+#    #+#             */
/*   Updated: 2024/03/17 21:03:57 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"
#include "pipex_bonus.h"

int	wait_process(pid_t *pids, int n)
{
	int	wstatus;
	int	exit_code;
	int	i;
	
	wstatus = 0;
	exit_code = EXIT_FAILURE;
	i = 0;
	while (i < n)
	{
		if (pids[i] > 0)
			waitpid(pids[i], &wstatus, 0);
		i++;
	}
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	*pids;
	int		i;

	if (argc < 5)
		return (pipex_error(ERROR_USE_BONUS));
	pids = pipex_malloc(sizeof(int) * (argc - 3), "pipex: main: malloc");
	if (pipe(pipe_fd) == -1)
	{
		pipex_perror("pipex: main: pipe");
		free(pids);
		return (EXIT_FAILURE);
	}
	pids[0] = process_infile(argv[1], argv[2], pipe_fd, envp);
	i = 0;
	while (++i < argc - 4)
		pids[i] = process_inter(argv[i + 2], pipe_fd, envp);
	pids[i] = process_outfile(argv[argc - 1], argv[argc - 2], pipe_fd, envp);
	close_pipe(pipe_fd);
	free(pids);
	return (wait_process(pids, argc - 3));
}

