/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:00:37 by stephane          #+#    #+#             */
/*   Updated: 2024/03/26 21:49:55 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <sys/types.h>
# include "pipex_const.h"
# include "cmd_to_argv.h"
# include "exit.h"

# define ERROR_USE "usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n"

#endif