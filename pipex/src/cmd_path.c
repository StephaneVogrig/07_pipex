/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:25 by stephane          #+#    #+#             */
/*   Updated: 2024/03/13 19:43:09 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_directory(char *path)
{
	int fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
		close(fd);
	return(fd >= 0);
}

t_bool	is_valid_path(char *path)
{
	if (is_directory(path))
	{
		ft_putstr_fd("pipex: ", STDERR_FD);
		ft_putstr_fd(path, STDERR_FD);
		ft_putstr_fd(": is a directory\n", STDERR_FD);
		free(path);
		exit(126);
	}
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("pipex: ", STDERR_FD);
		ft_putstr_fd(path, STDERR_FD);
		perror(path);
		free(path);
		exit(127);
	}
	return (SUCCESS);
}

char	*path_find(char	*paths, char *buf, char *cmd, int len)
{
	char	*temp;
// ft_putstr_fd(cmd, STDERR_FD);
// ft_putstr_fd("\n-----------------\n", STDERR_FD);
	while (*paths)
	{
// ft_putstr_fd(paths, STDERR_FD);
// ft_putstr_fd("...\n", STDERR_FD);
		temp = buf;
		while (*paths && *paths != ':')
			*temp++ = *paths++;
		*temp++ = '/';
		// str_to_token(cmd, temp);
		ft_strncpy(temp, cmd, len);
// ft_putstr_fd(buf, STDERR_FD);
// ft_putstr_fd("\n", STDERR_FD);
		if (access(buf, F_OK) == 0 && is_valid_path(buf))
			return (pipex_strndup(buf, temp + len - buf, TO_BE_FREE));
		if (*paths == ':')
			paths++;
	}
	ft_strncpy(buf, cmd, len);
	// str_to_token(cmd, buf);
	// ft_memmove(buf, temp, len + 1);
ft_putstr_fd("-----------------", STDERR_FD);
ft_putstr_fd(buf, STDERR_FD);
ft_putstr_fd("\n", STDERR_FD);
	cmd_not_found(buf, TO_BE_FREE);
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
ft_putstr_fd(cmd, STDERR_FD);
ft_putstr_fd("\n", STDERR_FD);

	paths = find_paths(envp);
	if (!paths || *cmd == '\0')
		cmd_not_found(cmd, NOT_BE_FREE);
	len_paths = ft_strlen(paths);
	len_cmd = len_next_token(cmd);
	cmd_path = str_malloc(len_paths + len_cmd + 2, "pipex: cmd_path");
	str_to_token(cmd, cmd_path);
// ft_putstr_fd(cmd_path, STDERR_FD);
// ft_putstr_fd("\n", STDERR_FD);
	// ft_strncpy(cmd_path, cmd, len_cmd);
	if (ft_strchr(cmd_path, '/') && is_valid_path(cmd_path))
		return (pipex_strndup(cmd_path, len_cmd, TO_BE_FREE));
	cmd_path = path_find(paths, cmd_path, cmd, len_cmd);
	return (cmd_path);
}
