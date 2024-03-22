/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:05:59 by stephane          #+#    #+#             */
/*   Updated: 2024/03/22 03:06:20 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	strtab_print(char **tabstr)
{
	if (tabstr == NULL)
		return ;
	while (*tabstr)
	{
		ft_printf("%s\n", *tabstr);
		tabstr++;
	}
}
