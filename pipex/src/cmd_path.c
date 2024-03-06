/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:25 by stephane          #+#    #+#             */
/*   Updated: 2024/03/06 11:15:50 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
{
	if (envp == NULL)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

char	*check_paths(char *cmd, char **paths)
{
	char	*temp;
	char	*cmd_path;

	temp = ft_strjoin("/", cmd);
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths, temp);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
		paths++;
	}
	free(temp);
	return (cmd_path);
}

t_bool	is_valid_path(char *str)
{
	if (ft_strchr(str, '/') && access(str, F_OK) == 0)
		return (TRUE);
	return (FALSE);
}

char	*cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;

	if (!cmd)
		return (NULL);
	if (is_valid_path(cmd))
		return (ft_strdup(cmd));
	paths = get_paths(envp);
	if (paths == NULL)
		return (NULL);
	cmd_path = check_paths(cmd, paths);
	ft_split_free(paths);
	return (cmd_path);
}
