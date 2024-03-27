/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:09:17 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/27 14:27:52 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	heredoc_write(t_list *heredoc, int fd)
{
	while (heredoc)
	{
		ft_putstr_fd(heredoc->content, fd);
		heredoc = heredoc->next;
	}
}

t_list	*get_heredoc(char *limiter)
{
	char	*line;
	t_list	*heredoc;
	int		len_lim;

	len_lim = ft_strlen(limiter);
	heredoc = NULL;
	line = ft_calloc(1, 1);
	if (!line)
		perror("pipex: get_heredoc: ft_calloc");
	while (line)
	{
		if (ft_strncmp(line, limiter, len_lim) == 0 && line[len_lim] == '\n')
			break ;
		if (!add_to_strlist(&heredoc, line))
			break ;
		line = get_next_line(STDIN_FD);
		if (!line)
			fd_printf(STDERR_FD, "%s (wanted \'%s\')\n", ERROR_HDOC, limiter);
	}
	if (line)
		free(line);
	return (heredoc);
}
