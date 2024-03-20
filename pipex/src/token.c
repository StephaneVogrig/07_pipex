/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:47 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/20 02:54:36 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

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

char	*malloc_next_token(char *str)
{
	int		size;
	char	*token;

	size = len_next_token(str);
	token = malloc(size + 1);
	if (!token)
	{
		perror("pipex: malloc_next_token");
		return (NULL);
	}
	return (token);
}
