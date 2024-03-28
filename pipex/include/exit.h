/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:00:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/28 22:46:40 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "pipex_const.h"

void	exit_on_is_directory(char *path, char *to_free, char **argv);
void	exit_on_acces_denied(char *path, char *to_free, char **argv);
void	exit_on_cmd_not_found(char **argv);
void	exit_on_open_error(char *file_path, int fd);
void	exit_perror(char *msg);

#endif
