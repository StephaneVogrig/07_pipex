/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:35:58 by stephane          #+#    #+#             */
/*   Updated: 2024/03/20 07:48:19 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		{
			waitpid(pids[i], &wstatus, 0);
		}
		i++;
	}
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	return (exit_code);
}

int	pipex(int heredoc_needed, int nb_cmd, char **cmd, char **envp)
{
	int		pipe_[2];
	pid_t	*pids;
	int		i;
	int		exit_code;

	pids = pipex_malloc(sizeof(int) * nb_cmd, "pipex: main: malloc");
	if(pipe(pipe_))
		exit_pipex("pipex: process_outfile: fork", pids, NULL, NULL);
	i = 0;
	if (heredoc_needed)
		pids[0] = process_heredoc(cmd++, pipe_, envp, pids);
	else
		pids[0] = process_infile(cmd++, pipe_, envp, pids);
	close(pipe_[WRITE]);
	while (i < (nb_cmd - 2) && pids[i] > -1)
		pids[++i] = process_pipes(cmd++, &pipe_[READ], envp, pids);
	if (i == (nb_cmd - 2) && pids[i - 2] > -1)
		pids[++i] = process_outfile(cmd, &pipe_[READ], envp, pids);
	exit_code = wait_process(pids, nb_cmd);
	free(pids);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	int		nb_cmd;
	int		heredoc_needed;

	if (argc < 5)
	{
		ft_putstr_fd(ERROR_USE_BONUS, STDERR_FD);
		return (EXIT_FAILURE);
	}
	argv++;
	heredoc_needed = (argc > 5) && (ft_strcmp(*argv, "here_doc") == 0);
	nb_cmd = argc - (3 + heredoc_needed);
	argv += 1 + heredoc_needed;
	return (pipex(heredoc_needed, nb_cmd, argv, envp));
}

