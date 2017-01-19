/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 02:29:50 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/19 05:59:50 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "../include/minishell.h"

char	cd_path_validity(char *path)
{
	DIR		*dir;

	if (!(dir = opendir(path)))
		return (0);
	closedir(dir);
	return (1);
}

char	is_binary(char *path)
{
	int		fd;
	char	buff[300];
	char	type;
	int		bytes;

	type = 0;
	fd = open(path, O_RDONLY);
	if ((bytes = read(fd, buff, 299)) > 0)
	{
		while (--bytes)
			if (buff[bytes] == '\0')
				type = 1;
	}
	close(fd);
	return (type);
}

int		countwd(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
		{
			while (*str && *str != ' ' && *str != '\t')
				++str;
			++count;
		}
		else
			++str;
	}
	return (count);
}

char	**clear_command(char *command, int j)
{
	char	**out;
	char	*tmp;
	int		i;

	if (!(out = (char**)malloc(sizeof(char*) * (countwd(command) + 1))))
		exit(EXIT_FAILURE);
	while (*command)
	{
		if (*command != ' ' && *command != '\t')
		{
			tmp = command;
			i = 0;
			while (*command && *command != ' ' && *command != '\t')
			{
				++i;
				++command;
			}
			out[++j] = ft_strsub(tmp, 0, i);
		}
		else
			++command;
	}
	out[++j] = NULL;
	return (out);
}
