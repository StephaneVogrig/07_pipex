/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:25 by stephane          #+#    #+#             */
/*   Updated: 2024/03/26 22:30:09 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_path.h"

t_bool	is_valid_path(char *path)
{
	if (is_directory(path))
	{
		fd_printf(STDERR_FD, "pipex: %s: is a directory\n", path);
		free(path);
		exit(126);
	}
	if (access(path, X_OK) == -1)
	{
		fd_printf(STDERR_FD, "pipex: %s\n", path);
		perror(path);
		free(path);
		exit(127);
	}
	return (SUCCESS);
}

char	*path_find(char	*paths, char *buf, char *cmd, int len)
{
	char	*temp;

	while (*paths)
	{
		temp = buf;
		while (*paths && *paths != ':')
			*temp++ = *paths++;
		*temp++ = '/';
		pipex_strncpy(temp, cmd, len);
		if (access(buf, F_OK) == 0 && is_valid_path(buf))
			return (pipex_strndup(buf, temp + len - buf));
		if (*paths == ':')
			paths++;
	}
	pipex_strncpy(buf, cmd, len);
	exit_on_cmd_not_found(buf, TO_BE_FREE);
	return (NULL);
}

char	*find_paths(char **envp)
{
	if (envp == NULL)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*cmd_path(char *cmd, char **envp)
{
	char	*cmd_path;
	char	*paths;
	int		len_cmd;
	int		len_paths;

	paths = find_paths(envp);
	if (!paths || *cmd == '\0')
		exit_on_cmd_not_found(cmd, NOT_BE_FREE);
	len_paths = ft_strlen(paths);
	len_cmd = len_next_token(cmd);
	cmd_path = malloc(len_paths + len_cmd + 2);
	if (!cmd_path)
		exit_perror("pipex: cmd_path");
	str_to_token(cmd, cmd_path);
	if (ft_strchr(cmd_path, '/') && is_valid_path(cmd_path))
		return (pipex_strndup(cmd_path, len_cmd));
	cmd_path = path_find(paths, cmd_path, cmd, len_cmd);
	return (cmd_path);
}
