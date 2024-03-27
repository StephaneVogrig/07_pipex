/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:25 by stephane          #+#    #+#             */
/*   Updated: 2024/03/27 17:33:40 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_path.h"

char	*cmd_path_strndup(char *str, int n, char **argv)
{
	char	*dup;

	dup = ft_strndup(str, n);
	free(str);
	if (!dup)
	{
		strtab_free(argv);
		exit_perror("pipex: cmd_path_strndup");
	}
	return (dup);
}

t_bool	is_valid_path(char *path, char **argv)
{
	if (is_directory(path))
	{
		fd_printf(STDERR_FD, "pipex: %s: is a directory\n", path);
		strtab_free(argv);
		free(path);
		exit(126);
	}
	if (access(path, X_OK) == -1)
	{
		fd_printf(STDERR_FD, "pipex: %s: %s\n", path, strerror(errno));
		strtab_free(argv);
		free(path);
		exit(127);
	}
	return (SUCCESS);
}

char	*path_find(char	*paths, char *buf, char **argv, int len)
{
	char	*temp;

	while (*paths)
	{
		temp = buf;
		while (*paths && *paths != ':')
			*temp++ = *paths++;
		*temp++ = '/';
		pipex_strncpy(temp, *argv, len);
		if (access(buf, F_OK) == 0 && is_valid_path(buf, argv))
			return (cmd_path_strndup(buf, temp + len - buf, argv));
		if (*paths == ':')
			paths++;
	}
	free(buf);
	exit_on_cmd_not_found(argv);
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

char	*cmd_path(char **argv, char **envp)
{
	char	*cmd_path;
	char	*paths;
	int		len_cmd;

	len_cmd = ft_strlen(*argv);
	paths = find_paths(envp);
	cmd_path = malloc(ft_strlen(paths) + len_cmd + 2);
	if (!cmd_path)
	{
		perror("pipex: cmd_path");
		return (NULL);
	}
	pipex_strncpy(cmd_path, *argv, len_cmd);
	if (ft_strchr(cmd_path, '/') && is_valid_path(cmd_path, argv))
		return (cmd_path_strndup(cmd_path, len_cmd, argv));
	if (!paths || **argv == '\0')
	{
		free(cmd_path);
		exit_on_cmd_not_found(argv);
	}
	cmd_path = path_find(paths, cmd_path, argv, len_cmd);
	return (cmd_path);
}
