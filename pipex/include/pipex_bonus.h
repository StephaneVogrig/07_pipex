/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:21:26 by stephane          #+#    #+#             */
/*   Updated: 2024/03/17 20:01:17 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define ERROR_USE_BONUS "\
usage: \n\
./pipex <file1> <cmd1> ... <cmdn> <file2>\n\
./pipex here_doc limiter <cmd1> ... <cmdn> <file>\n\
"

int		process_inter(char *cmd, int *pipe_in, char **envp);
void	*pipex_malloc(int size, char *error_msg);

#endif