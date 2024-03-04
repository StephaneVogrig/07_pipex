
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
