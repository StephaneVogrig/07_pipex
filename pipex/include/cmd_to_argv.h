/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_argv.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:55:14 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/20 03:58:38 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_TO_ARGV_H
# define CMD_TO_ARGV_H

# include <stdio.h>
# include "libft.h"
# include "token.h"

char	**cmd_to_argv(char *str);

#endif