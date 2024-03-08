/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:15:04 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/08 01:05:52 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*end_quote(char *str, char quote)
{
	while (*str != quote)
		str++;
	return (str);
}

t_bool	tokens_add(char *str, t_list **tokens)
{
	t_list	*new_node;

	if (!str)
	{
		perror("pipex: new_node");
		ft_lstclear(tokens, &free);
		return (ERROR);
	}
	new_node = ft_lstnew(str);
	if (!new_node)
	{
		perror("pipex: new_node");
		free(str);
		ft_lstclear(tokens, &free);
		return (ERROR);
	}
	ft_lstadd_back(tokens, new_node);
	return (SUCCESS);
}

char	*end_token(char *str)
{
	while (*str && *str != ' ')
	{
		if (*str == '\'' || *str == '\"')
			str = end_quote(str, *str);
		str++;
	}
	return (str);
}

t_list *get_token_list(char *str)
{
	char	*start;
	t_list	*tokens;

	if (!str)
		return (NULL);
	tokens = NULL;
	start = str;
	while (*str)
	{
		while (*str == ' ')
			str++;
		start = str;
		str = end_token(str);
		if (str > start)
			if(!tokens_add(ft_strndup(start, str - start), &tokens))
				return (NULL);
	}
	return (tokens);
}

char **strlist_to_strtab(t_list *strlist)
{
	int		nbr_elem;
	char	**strtab;
	char	**ret;
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
	ret = strtab;
	while (nbr_elem--)
	{
		*strtab++ = strlist->content;
		temp = strlist->next;
		free(strlist);
		strlist = temp;
	}
	*strtab = NULL;
	return (ret);
}

char	**get_argv(char *str)
{
	char	**argv;
	t_list	*tokens;

	if (!str)
		return (NULL);
	tokens = get_token_list(str);
	if (tokens == NULL)
		return (NULL);
// ft_putstr_fd("\n---------------------------------\n", STDERR_FD);
// ft_putstr_fd("tokens :\n", STDERR_FD);
// strlist_print_fd(tokens, STDERR_FD);
// ft_putstr_fd("---------------------------------\n", STDERR_FD);
	argv = strlist_to_strtab(tokens);
// ft_putstr_fd("argv :\n", STDERR_FD);
// strtab_print_fd(argv, STDERR_FD);
// // ft_printf("%p\n", argv);
// ft_putstr_fd("---------------------------------\n", STDERR_FD);
	if (!argv)
	{
		ft_lstclear(&tokens, &free);
		return (NULL);
	}
	return (argv);
}
