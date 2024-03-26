/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:52:14 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/26 22:31:31 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

void	pipex_strncpy(char *dest, char *src, int n)
{
	while (n-- && *src)
		*dest++ = *src++;
	*dest = '\0';
}

char	*pipex_strndup(char *str, int n)
{
	char	*dup;

	dup = ft_strndup(str, n);
	free(str);
	if (!dup)
		exit_perror("pipex_strndup");
	return (dup);
}
