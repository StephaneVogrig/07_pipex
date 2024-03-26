/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_argv.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:55:14 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/26 21:48:00 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_TO_ARGV_H
# define CMD_TO_ARGV_H

# include "cmd_path.h"

void	exec_cmd(int fd_in, int fd_out, char *cmd, char **envp);
char	**cmd_to_argv(char *str);

#endif