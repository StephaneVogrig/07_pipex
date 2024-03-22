/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:52:14 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/22 02:47:27 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

void	ft_strncpy(char *dest, char *src, int n)
{
	while (n-- && *src)
		*dest++ = *src++;
	*dest = '\0';
}

char	*str_malloc(int size, const char *error_msg)
{
	char	*str;

	str = malloc(size);
	if (!str)
	{
		perror(error_msg);
		exit(EXIT_FAILURE);
	}
	return (str);
}

char	*pipex_strndup(char *str, int n, t_bool to_be_free)
{
	char	*dup;

	dup = ft_strndup(str, n);
	if (to_be_free && str != NULL)
		free(str);
	if (!dup)
	{
		perror("pipex_strndup");
		exit(EXIT_FAILURE);
	}
	return (dup);
}

char	*pipex_strjoin(char *str1, char *str2)
{
	char	*str;

	str = ft_strjoin(str1, str2);
	if (!str)
	{
		perror("pipex: pipex_strjoin");
		return (NULL);
	}
	return (str);
}
