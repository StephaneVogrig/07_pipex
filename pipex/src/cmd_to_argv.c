/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:52:08 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/20 07:42:25 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cmd_to_argv.h"

char	**tokenlist_to_argv(t_list *strlist)
{
	int		nbr_elem;
	char	**strtab;
	char	**argv;
	t_list	*temp;

	if (!strlist)
		return (NULL);
	nbr_elem = ft_lstsize(strlist);
	strtab = malloc(sizeof(strtab) * (nbr_elem + 1));
	if (!strtab)
	{
		perror("pipex: strlist_to_strtab");
		return (NULL);
	}
	argv = strtab;
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

t_bool	add_to_tokenlist(t_list **tokenlist, char *token)
{
	t_list	*new_node;

	new_node = ft_lstnew(token);
	if (!new_node)
	{
		perror("pipex: add_to_tokenlist");
		return (FAILURE);
	}
	ft_lstadd_back(tokenlist, new_node);
	return (SUCCESS);
}

t_bool	str_to_tokenlist(char *str, t_list **tokenlist)
{
	t_bool	ok;
	char	*token;

	token = NULL;
	while (*str)
	{
		token = malloc_next_token(str);
		ok = (token != NULL);
		if (ok)
		{
			str = str_to_token(str, token);
			ok = add_to_tokenlist(tokenlist, token);
		}
		if (!ok)
			break ;
		while (*str == ' ')
			str++;
	}
	if (ok)
		return (SUCCESS);
	ft_lstclear(tokenlist, &free);
	return (FAILURE);
}

char	**cmd_to_argv(char *str)
{
	t_list	*tokenlist;

	tokenlist = NULL;
	if (str_to_tokenlist(str, &tokenlist) == SUCCESS)
		return (tokenlist_to_argv(tokenlist));
	return (NULL);
}
