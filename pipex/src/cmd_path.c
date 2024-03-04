/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:25 by stephane          #+#    #+#             */
/*   Updated: 2024/03/03 13:57:30 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

char	**envp_to_paths(char **envp)
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

char	*cmd_path(char **cmd, char **envp)
{
	char	**paths;
	char	*temp;
	char	*cmd_path;
	int		i;

	if (!cmd)
		return (NULL);
	if (access(*cmd, F_OK) == 0)
		return (*cmd);
	paths = envp_to_paths(envp);
	if (paths == NULL)
		return (*cmd);
	cmd_path = NULL;
	temp = ft_strjoin("/", *cmd);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], temp);
		if (access(cmd_path, F_OK) == 0)
			break;
		free(cmd_path);
		i++;
		cmd_path = NULL;
	}
	ft_split_free(paths);
	free(temp);
	return (cmd_path);
}
