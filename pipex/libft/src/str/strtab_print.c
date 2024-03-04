/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:05:59 by stephane          #+#    #+#             */
/*   Updated: 2024/03/02 23:21:45 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
