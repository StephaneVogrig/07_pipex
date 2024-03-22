/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:09:17 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/22 02:58:38 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	heredoc_write(t_list *hd_lst, int fd)
{
	while (hd_lst)
	{
		ft_putstr_fd(hd_lst->content, fd);
		hd_lst = hd_lst->next;
	}
}

void	*calloc_error(char *msg, char *limiter)
{
	perror(msg);
	free(limiter);
	return (NULL);
}

t_list	*get_heredoc(char *limiter)
{
	char	*line;
	t_list	*hd_list;
	t_list	*new_node;

	limiter = pipex_strjoin(limiter, "\n");
	if (!limiter)
		return (NULL);
	line = ft_calloc(1, 1);
	if (!line)
		return (calloc_error("pipex: get_herdoc: ft_calloc", limiter));
	hd_list = NULL;
	while (line && ft_strcmp(line, limiter) != 0)
	{
		new_node = ft_lstnew(line);
		if (!new_node)
		{
			free(line);
			ft_lstclear(&hd_list, *free);
			return (NULL);
		}
		ft_lstadd_back(&hd_list, new_node);
		line = get_next_line(STDIN_FD);
	}
	return (hd_list);
}
