/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 05:12:25 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/22 03:08:57 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	buffer_save_add(t_buflst **list, t_buflst *new)
{
	t_buflst	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	buffer_save(t_buffer *buffer)
{
	t_buflst	*new_save;
	int			i;

	new_save = malloc(sizeof(t_buflst));
	if (!new_save)
	{
		buffer->offset = 0;
		return ;
	}
	new_save->next = NULL;
	i = 0;
	while (i < BUFFER_SIZE)
	{
		new_save->data[i] = buffer->data[i];
		i++;
	}
	buffer_save_add(&buffer->save, new_save);
	buffer->offset = 0;
}
