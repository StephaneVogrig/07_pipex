/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:52:14 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/27 17:34:20 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

void	pipex_strncpy(char *dest, char *src, int n)
{
	while (n-- && *src)
		*dest++ = *src++;
	*dest = '\0';
}

t_bool	add_to_strlist(t_list **strlist, char *str)
{
	t_list	*new_node;

	new_node = ft_lstnew(str);
	if (!new_node)
	{
		perror("pipex: add_to_strlist");
		ft_lstclear(strlist, &free);
		return (FAILURE);
	}
	ft_lstadd_back(strlist, new_node);
	return (SUCCESS);
}

char	**argv_empty(void)
{
	char	**argv;
	char	*empty_str;

	argv = NULL;
	empty_str = calloc(1, 1);
	if (!empty_str)
		exit_perror("pipex: argv_empty: calloc");
	argv = malloc(sizeof(char *) * 2);
	if (!argv)
	{
		free(empty_str);
		exit_perror("pipex: argv_empty: malloc");
	}
	argv[0] = empty_str;
	argv[1] = NULL;
	return (argv);
}
