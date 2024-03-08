/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_print_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:07:56 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/07 23:12:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	strtab_print_fd(char **tabstr, int fd)
{
	if (tabstr == NULL)
		return ;
	while (*tabstr)
	{
		ft_putstr_fd(*tabstr, fd);
		ft_putchar_fd('\n', fd);
		tabstr++;
	}
}
