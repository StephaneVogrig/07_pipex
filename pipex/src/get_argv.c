/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:15:04 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/09 16:10:29 by svogrig          ###   ########.fr       */
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

char	*fill_inside_quote(char *current, char *str, char quote)
{
	str++;
	while (*str && *str != quote)
		*current++ = *str++;
	if (*str)
		str++;
	return (str);
}

t_list	*get_next_token(char *str, char *buffer)
{
	char	*current;
	t_list	*token;

	current = buffer;
	token = NULL;
	while (*str == ' ')
		str++;
	while (*str && *str != ' ')
	{
		if (*str == '\'' || *str == '\"')
		{
			char	quote = *str;
			str++;
			while (*str && *str != quote)
				*current++ = *str++;
			if (*str)
				str++;
		}
		else
			*current++ = *str++;
	}
	if (current != buffer)
		token = ft_lstnew(ft_strndup(buffer, current - buffer));
	return (token);
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

t_bool	buffer_to_tokens(char *buffer, char *current, t_list **tokens)
{
	t_list	*token;
	char 	*str;

	str = ft_strndup(buffer, current - buffer);
	if (!str)
	{
		perror("pipex: buffer_to_token: ft_strndup");
		ft_lstclear(tokens, &free);
		return (ERROR);
	}
	token = ft_lstnew(str);
	if (!token)
	{
		perror("pipex: get_token_list: new_token");
		ft_lstclear(tokens, &free);
		return (ERROR);
	}
	ft_lstadd_back(tokens, token);
	return (SUCCESS);
}

char	*add_token(char *str, char *buffer, t_list **tokens)
{
	char	*current;
	char	quote;

	current = buffer;
	while (*str && *str != ' ')
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			while (*str && *str != quote)
				*current++ = *str++;
			if (*str)
				str++;
		}
		else
			*current++ = *str++;
	}
	if (!buffer_to_tokens(buffer, current, tokens))
		return (NULL);
	return (str);
}

char	*substr_to_buffer(char *str, char *buffer)
{
	while (*str && *str != ' ')
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			while (*str && *str != quote)
				*buffer++ = *str++;
			if (*str)
				str++;
		}
		else
			*buffer++ = *str++;
	}
	
}

char **tokenlist_to_argv(t_list *strlist)
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
	int		size;
	char	*token;

	ok = SUCCESS;
	while (*str)
	{
		size = size_next_token(str);
		ok = malloc_token(&token, size + 1);
		if (!ok)
			break;
		str = str_to_token(str, token);
		ok = add_to_tokenlist(tokenlist, token);
		if (!ok)
			break;
		while (*str == ' ')
			str++;
	}
	if (ok)
		return (SUCCESS);
	ft_lstclear(&tokenlist, &free);
	return (FAILURE);
}

char	**get_argv(char *str)
{
	t_list	*tokenlist;

	tokenlist = NULL;
	if (str_to_tokenlist(str, &tokenlist) == SUCCESS)
		return (tokenlist_to_argv(tokenlist));
	return (NULL);
}
