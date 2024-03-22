
char	*paths_to_cmd(char **paths, char *cmd_name)
{
	char	*temp1;
	char	*cmd_path;
	
	if (paths == NULL)
		return (cmd_name);
	temp1 = ft_strjoin("/", cmd_name);
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths, temp1);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		paths++;
	}
	free(temp1);
	return (NULL);
}

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
			break ;
		free(cmd_path);
		cmd_path = cmd;
		paths++;
	}
	free(temp);
	if (!cmd_path)
		return (NULL);
	if (cmd_path == cmd)
		cmd_not_found(cmd);
	if (cmd_path && !is_valid_path(cmd_path))
		cmd_path = NULL;
	return (cmd_path);
}
