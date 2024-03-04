/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:16:47 by stephane          #+#    #+#             */
/*   Updated: 2024/03/02 23:49:30 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

void	strtab_free(char **strtab)
{
	if (strtab == NULL)
		return ;
	while (*strtab)
	{
		free(*strtab);
		strtab++;
	}
}