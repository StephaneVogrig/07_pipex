/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_malloc_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:54:03 by stephane          #+#    #+#             */
/*   Updated: 2024/03/17 19:57:20 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	*pipex_malloc(int size, char *error_msg)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror(error_msg);
		exit(EXIT_FAILURE);		
	}
	return (ptr);
}