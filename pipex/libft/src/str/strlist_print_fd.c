/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlist_print_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:02:05 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/07 22:18:51 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	strlist_print_fd(t_list *strlist, int fd)
{
	while (strlist)
	{
		ft_putstr_fd(strlist->content, fd);
		ft_putchar_fd('\n', fd);
		strlist = strlist->next;
	}
}
