/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 02:29:50 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/17 22:02:53 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/minishell.h"

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

void	treat_current(char *path)
{
	char	*tmp;
	char	*cwd;
	char	buff[4097];

	if (!ft_strcmp(path, "."))
		return ;
	else if (!ft_strcmp(path, ".."))
	{
		cwd = getcwd(buff, 4097);
		if (ft_strlen(cwd) > 1)
		{
			tmp = ft_strsub(cwd, 0, ft_strrchr(cwd, '/') - cwd);
			chdir(tmp);
			free(tmp);
		}
	}
	else if (*path == '/')
		chdir(path);
	else
	{
		cwd = getcwd(buff, 4097);
		if (!ft_strcmp(cwd, "/"))
			tmp = ft_strjoin(cwd, path);
		else
			tmp = ft_strstrjoin(cwd, "/", path);
		chdir(tmp);
		free(tmp);
	}
}

void	change_prompt(char *path, t_env *env)
{
	char	*tmp;
	char	*path2;
	int		i;

	if (!(ft_strchr(path, '/')) || !ft_strcmp(path, "/"))
		treat_current(path);
	else
	{
		if (*path == '/')
			i = ft_strchr(path + 1, '/') - path;
		else
			i = ft_strchr(path, '/') - path;
		tmp = ft_strsub(path, 0, i);
		path2 = ft_strsub(path, i + 1, ft_strlen(path) - i - 1);
		treat_current(tmp);
		free(tmp);
		change_prompt(path2, env);
		free(path2);
	}
}

char	*get_with_tilde(char *path, t_env *env)
{
	char	*home;
	char	*tmp;
	int		i;

	i = -1;
	if (!(home = find_env(env, "HOME")))
		return (ft_strdup(path));
	while (*home && path[++i] && (path[i] == *home))
		++home;
	if (*home)
		return (ft_strdup(path));
	if (!path[i + 1])
		return (ft_strdup("~"));
	home = ft_strsub(path + i + 1, 0, ft_strlen(path) - i - 1);
	tmp = ft_strjoin("~", home);
	free(home);
	return (tmp);
}