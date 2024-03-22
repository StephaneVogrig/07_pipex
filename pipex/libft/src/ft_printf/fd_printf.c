/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 03:43:28 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/22 03:09:23 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	buffer_print_fd(t_buffer buffer, int fd)
{
	t_buflst	*tmp;

	while (buffer.save)
	{
		tmp = buffer.save;
		buffer.writed += write(fd, tmp->data, BUFFER_SIZE);
		buffer.save = tmp->next;
		free(tmp);
	}
	return (write(fd, buffer.data, buffer.offset) + buffer.writed);
}

int	fd_printf(int fd, const char *format, ...)
{
	va_list		args;
	t_buffer	buffer;
	ssize_t		writed;
	int			spec_errors;

	spec_errors = 0;
	buffer.offset = 0;
	buffer.writed = 0;
	buffer.save = NULL;
	va_start(args, format);
	while (format && *format)
	{
		while (*format && *format != '%')
			buffer_add_char(&buffer, *format++, 1);
		if (*format == '%')
			format = parse_arg(format + 1, &buffer, args, &spec_errors);
	}
	va_end(args);
	writed = buffer_print_fd(buffer, fd);
	if (!format)
		return (-1);
	return (writed);
}
