/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:16:47 by stephane          #+#    #+#             */
/*   Updated: 2024/03/22 03:06:59 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	strtab_free(char **strtab)
{
	char	**current;

	if (strtab == NULL)
		return ;
	current = strtab;
	while (*current)
	{
		free(*current);
		current++;
	}
	free(strtab);
}
