/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:15:04 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/10 03:51:15 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**tokenlist_to_argv(t_list *strlist)
{
	int		nbr_elem;
	char	**strtab;
	char	**argv;
	t_list	*temp;

	if (!strlist)
		return (NULL);
	nbr_elem = ft_lstsize(strlist);
	strtab = malloc(sizeof(strtab) * (nbr_elem + 1));
	if (!strtab)
	{
		perror("pipex: strlist_to_strtab");
		return (NULL);
	}
	argv = strtab;
	while (nbr_elem--)
	{
		*strtab++ = strlist->content;
		temp = strlist->next;
		free(strlist);
		strlist = temp;
	}
	*strtab = NULL;
	return (argv);
}

t_bool	add_to_tokenlist(t_list **tokenlist, char *token)
{
	t_list	*new_node;

	new_node = ft_lstnew(token);
	if (!new_node)
	{
		perror("pipex: add_to_tokenlist");
		return (FAILURE);
	}
	ft_lstadd_back(tokenlist, new_node);
	return (SUCCESS);
}

t_bool	str_to_tokenlist(char *str, t_list **tokenlist)
{
	t_bool	ok;
	char	*token;

	token = NULL;
	while (*str)
	{
		token = malloc_next_token(str);
		ok = (token != NULL);
		if (ok)
		{
			str = str_to_token(str, token);
			ok = add_to_tokenlist(tokenlist, token);
		}
		if (!ok)
			break ;
		while (*str == ' ')
			str++;
	}
	if (ok)
		return (SUCCESS);
	ft_lstclear(tokenlist, &free);
	return (FAILURE);
}

char	**get_argv(char *str)
{
	t_list	*tokenlist;

	tokenlist = NULL;
	if (str_to_tokenlist(str, &tokenlist) == SUCCESS)
		return (tokenlist_to_argv(tokenlist));
	return (NULL);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	*exe_path;
	char	**exe_argv;

	while (*cmd == ' ')
		cmd++;
	if (*cmd == '\0')
	{
		ft_putstr_fd("command \'\' not found\n", STDERR_FD);
		exit(EXIT_FAILURE);
	}
	exe_argv = get_argv(cmd);
	if (!exe_argv)
		exit(EXIT_FAILURE);
	exe_path = cmd_path(exe_argv[0], envp);
	if (!exe_path)
	{
		strtab_free(exe_argv);
		exit(127);
	}
	execve(exe_path, exe_argv, envp);
	perror("pipex");
	strtab_free(exe_argv);
	free(exe_path);
	exit(EXIT_FAILURE);
}
