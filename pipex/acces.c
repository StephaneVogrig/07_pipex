/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acces.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 03:10:35 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/20 03:07:33 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int	is_directory(char *path)
{
	int fd = open(path, O_DIRECTORY);
	if (fd != -1)
		close(fd);
	return(fd != -1);
}

	// perror("is_directory");

int	main(int argc, char **argv)
{
	char	buffer[100];
	int 	size;	

	if (argc < 2)
		return (0);
	if(is_directory(argv[1]))
		printf("%s is directory\n", argv[1]);
	else
		printf("%s is not directory\n", argv[1]);

	return (0);
}