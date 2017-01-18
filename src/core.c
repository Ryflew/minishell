/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 21:16:56 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/18 05:39:52 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <unistd.h>
#include "../include/minishell.h"

char	go_builtins(char **av, t_env **env, char **path)
{
	if (!ft_strcmp(av[0], "echo"))
		echo(av, *env);
	else if (!ft_strcmp(av[0], "cd"))
		cd(av, *env, path);
	else if (!ft_strcmp(av[0], "setenv"))
		set_env(av, env);
	else if (!ft_strcmp(av[0], "unsetenv"))
		unset_env(av, env);
	else if (!ft_strcmp(av[0], "env"))
		env_command(av, *env);
	else if (!ft_strcmp(av[0], "exit"))
		exit(EXIT_SUCCESS);
	else
		return (0);
	return (1);
}

char	check_path(char *command, char *path)
{
	DIR			*dir;
	t_dirent	*ent;
	t_stat		file;
	char		*tmp;

	(void)command;
	if (!(dir = opendir(path)))
		return (0);
	while ((ent = readdir(dir)))
	{
		if (!ft_strcmp(ent->d_name, command))
		{
			tmp = ft_strstrjoin(path, "/", ent->d_name);
			if (!stat(tmp, &file) && S_ISREG(file.st_mode) && is_binary(tmp) \
				&& (file.st_mode & S_IXUSR) && (file.st_mode & S_IXGRP) \
				&& (file.st_mode & S_IXOTH))
			{
				free(tmp);
				closedir(dir);
				return (1);
			}
			free(tmp);
		}
	}
	closedir(dir);
	return (0);
}

char	go_path(char **av, t_env *env)
{
	char	*content;
	char	**tmp;
	int		i;

	if (!(content = find_env(env, "PATH")))
		return (0);
	tmp = ft_strsplit(content, ':');
	content = av[0];
	if (ft_strrchr(content, '/'))
		content = ft_strrchr(content, '/') + 1;
	i = -1;
	while (tmp[++i])
	{
		if (check_path(content, tmp[i]))
		{
			run_binary(ft_strstrjoin(tmp[i], "/", content), av, env);
			ft_strdelpp(&tmp);
			return (1);
		}
	}
	ft_strdelpp(&tmp);
	return (0);
}

void	go_core(char *command, t_env **env, char **path)
{
	char	**av;
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	av = clear_command(command, -1);
	while (av[j])
	{
		tmp = next_command(&av, &i, &j);
		if (!tmp)
			continue ;
		if (go_builtins(tmp, env, path))
			;
		else if (go_path(tmp, *env))
			;
		else
		{
			ft_putstr(av[0]);
			ft_putendl(": Command not found.");
		}
		ft_strdelpp(&tmp);
	}
	ft_strdelpp(&av);
}
