/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:52:08 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/27 17:33:11 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_to_argv.h"

char	**tokenlist_to_argv(t_list *strlist)
{
	int		nbr_elem;
	char	**strtab;
	char	**argv;
	t_list	*temp;

	if (!strlist)
		return (NULL);
	nbr_elem = ft_lstsize(strlist);
	argv = malloc(sizeof(argv) * (nbr_elem + 1));
	if (!argv)
	{
		perror("pipex: tokenlist_to_argv");
		return (NULL);
	}
	strtab = argv;
	while (nbr_elem--)
	{
		*strtab++ = strlist->content;
		temp = strlist->next;
		free(strlist);
		strlist = temp;
	}
	*strtab = NULL;
	return (argv);
}

char	*str_to_token(char *str, char *token)
{
	char	quote;

	while (*str && *str != ' ')
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			while (*str && *str != quote)
				*token++ = *str++;
			if (*str)
				str++;
			continue ;
		}
		*token++ = *str++;
	}
	*token = '\0';
	return (str);
}

int	len_next_token(char *str)
{
	int		size;
	char	quote;

	size = 0;
	while (*str && *str != ' ')
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			while (*str && *str++ != quote)
				size++;
			if (*str)
				str++;
			continue ;
		}
		str++;
		size++;
	}
	return (size);
}

char	*add_next_token(char *str, t_list **tokenlist)
{
	char	*token;

	token = malloc(len_next_token(str) + 1);
	if (!token)
	{
		perror("pipex: add_next_token");
		ft_lstclear(tokenlist, &free);
		return (NULL);
	}
	str = str_to_token(str, token);
	if (!add_to_strlist(tokenlist, token))
		return (NULL);
	return (str);
}

char	**cmd_to_argv(char *str)
{
	t_list	*tokenlist;
	char	**argv;

	if (*str == '\0')
		return (argv_empty());
	tokenlist = NULL;
	while (*str)
	{
		str = add_next_token(str, &tokenlist);
		if (!str)
			return (NULL);
		while (*str == ' ')
			str++;
	}
	argv = tokenlist_to_argv(tokenlist);
	if (!argv)
		ft_lstclear(&tokenlist, &free);
	return (argv);
}
