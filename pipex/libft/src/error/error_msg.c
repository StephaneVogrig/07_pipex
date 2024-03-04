/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:02:06 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/02 12:22:58 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

t_bool	error_msg(char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FD);
	write(STDERR_FD, "\n", 1);
	return (ERROR);
}
