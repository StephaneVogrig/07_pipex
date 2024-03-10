/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:25 by stephane          #+#    #+#             */
/*   Updated: 2024/03/10 05:49:13 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
{
	char	**paths;

	if (envp == NULL)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			paths = ft_split(*envp + 5, ':');
			if (paths)
				return (paths);
			perror("pipex: get_paths");
			return (NULL);
		}
		envp++;
	}
	return (NULL);
}

char	*pipex_join(char *str1, char *str2)
{
	char	*str;

	str = ft_strjoin(str1, str2);
	if (!str)
	{
		perror("pipex: pipex_join");
		return (NULL);
	}
	return (str);
}

char	*check_paths(char *cmd, char **paths)
{
	char	*temp;
	char	*cmd_path;

	temp = pipex_join("/", cmd);
	if (!temp)
		return (NULL);
	while (*paths)
	{
		cmd_path = pipex_join(*paths, temp);
		if (!cmd_path || access(cmd_path, F_OK) == 0)
		{
			free(temp);
			return (cmd_path);
		}
		free(cmd_path);
		paths++;
	}
	free(temp);
	ft_putstr_fd(cmd, STDERR_FD);
	ft_putstr_fd(": command not found\n", STDERR_FD);
	return (NULL);
}

char	*check_path(char *cmd)
{
	char	*cmd_path;

	if (access(cmd, F_OK) == 0)
	{
		cmd_path = ft_strdup(cmd);
		if (cmd_path)
			return (cmd_path);
		perror("pipex: check_path");
		return (NULL);
	}
	ft_putstr_fd("pipex: ", STDERR_FD);
	perror(cmd);
	return (NULL);
}

char	*cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;

	if (!cmd)
		return (NULL);
	if (!*cmd)
	{
		ft_putstr_fd(": command not found\n", STDERR_FD);
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
		return (check_path(cmd));
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	cmd_path = check_paths(cmd, paths);
	ft_split_free(paths);
	return (cmd_path);
}
