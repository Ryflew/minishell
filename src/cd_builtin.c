/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 15:12:00 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/15 23:46:03 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include "../include/minishell.h"

void	change_path(char *path, t_env *env)
{
	char	**av;

	if(!(av = (char**)malloc(sizeof(char*) * 4)))
		exit(EXIT_FAILURE);
	av[0] = ft_strdup("setenv");
	av[1] = ft_strdup("PWD");
	if (path[0] == '/')
		av[2] = ft_strdup(path);
	else
		av[2] = ft_strjoin("/", path);
	av[3] = NULL;
	set_env(av, &env);
	ft_strdelpp(&av);
	chdir(path);
}

char	cd_path_validity(char *path)
{
	DIR		*dir;

	if (!(dir = opendir(path)))
		return (0);
	closedir(dir);
	return (1);
}

void	cd_home(t_env *env)
{
	char	*content;

	if (!(content = find_env(env, "HOME")))
		errexit("cd", "HOME not set.");
	else
	{
		if (cd_path_validity(content))
			change_path(content, env);
		else
			errexit("cd", "Can't change to home directory.");
	}
}

void	cd_current_dir(char *path, t_env *env)
{
	char	*cwd;
	char	buff[4097];

	cwd = NULL;
	if (cd_path_validity(path))
	{
		cwd = getcwd(buff, 4097);
		if (cwd)
		{
			cwd = ft_strstrjoin(cwd, "/", path);
			change_path(cwd, env);
		}
		else
			errexit("cd", "Absolute path too large.");
		free(cwd);
	}
	else
		errexit("cd", "No such file or directory.");
}

void	cd_tilde(char *str, t_env *env)
{
	char	*tmp;
	char	*tmp2;

	if (!(tmp = find_env(env, "HOME")))
	{
		errexit("cd", "HOME not set.");
		return ;
	}
	tmp2 = ft_strjoin(tmp, str + 1);
	change_path(tmp2, env);
	free(tmp2);
}

void	cd(char **av, t_env *env)
{
	if (!*++av || (*av[0] == '~' && !(*(*av + 1))))
		cd_home(env);
	else if (*(av + 1))
		errexit("cd", "Too many arguments.");
	else if (*av[0] == '/')
	{
		if (cd_path_validity(*av))
			change_path(*av, env);		
		else
		{
			if (!lstat(*av, NULL))
				errexit("cd", "Not a directory.");
			else
				errexit("cd", "No such file or directory.");
		}
	}
	else if (*av[0] == '~')
		cd_tilde(*av, env);
	else
		cd_current_dir(*av, env);
}
