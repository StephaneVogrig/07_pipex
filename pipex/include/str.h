/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:50:36 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/26 23:27:31 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stdio.h>
# include "libft.h"
# include "exit.h"

void	pipex_strncpy(char *dest, char *src, int n);
char	*str_malloc(int size, const char *error_msg);
char	*pipex_strndup(char *str, int n);

#endif
