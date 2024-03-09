/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:47 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/09 15:54:21 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	size_next_token(char *str)
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
			continue;
		}
		*token++ = *str++;
	}
	return (str);
}

t_bool	malloc_token(char **token, int size)
{
	*token = malloc(size);
	if (!*token)
	{
		perror("pipex: malloc_token");
		return (FAILURE);
	}
	return (SUCCESS);
}
