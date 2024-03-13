/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printacces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 04:05:18 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/13 04:11:02 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	if (access(argv[1], F_OK) == -1)
		perror(argv[1]);
	if (access(argv[1], R_OK) == -1)
		perror(argv[1]);
	if (access(argv[1], X_OK) == -1)
		perror(argv[1]);
	if (access(argv[1], W_OK) == -1)
		perror(argv[1]);

	return (0);
}