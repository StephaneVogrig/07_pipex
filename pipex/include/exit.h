/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:00:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/26 22:17:35 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "pipex_const.h"

void	exit_on_cmd_not_found(char *cmd, t_bool to_be_free);
void	exit_on_open_error(char *file_path, int fd);
void	exit_perror(char *msg);

#endif
