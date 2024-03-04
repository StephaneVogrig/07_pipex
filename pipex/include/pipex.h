/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:00:37 by stephane          #+#    #+#             */
/*   Updated: 2024/03/03 13:41:49 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft.h"

# define READ 0
# define WRITE 1

char	*cmd_path(char **cmd, char **envp);

#endif