/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 15:12:00 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/20 20:00:11 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../include/minishell.h"

void	change_path(char *path, t_env *env, char **prompt)
{
	char	**av;
	char	buff[4097];
	char	*tmp;

	if (!(av = (char**)malloc(sizeof(char*) * 4)))
		exit(EXIT_FAILURE);
	av[0] = ft_strdup("setenv");
	av[1] = ft_strdup("OLDPWD");
	av[2] = ft_strdup(getcwd(buff, 4097));
	av[3] = NULL;
	tmp = ft_strdup(path);
	set_env(av, &env);
	ft_strdelpp(&av);
	change_prompt(tmp, env);
	free(tmp);
	if (!(av = (char**)malloc(sizeof(char*) * 4)))
		exit(EXIT_FAILURE);
	av[0] = ft_strdup("setenv");
	av[1] = ft_strdup("PWD");
	av[2] = ft_strdup(getcwd(buff, 4097));
	av[3] = NULL;
	free(*prompt);
	*prompt = get_with_tilde(getcwd(buff, 4097), env);
	set_env(av, &env);
	ft_strdelpp(&av);
}

void	print_cd_error(char *tmp, char *path)
{
	t_stat	file;

	if (!lstat(tmp, &file) && S_ISREG(file.st_mode))
		errexit(path, "Not a directory.");
	else if (access(tmp, F_OK) == -1)
		errexit("cd", "No such file or directory.");
	else
		errexit(tmp, "Permission denied.");
}

void	cd_current_dir(char *path, t_env *env, char **prompt)
{
	char	*cwd;
	char	*tmp;
	char	buff[4097];

	if (!(cwd = getcwd(buff, 4097)))
	{
		errexit(path, "Permission denied.");
		return ;
	}
	if (cd_path_validity(path))
	{
		if (cwd)
			change_path(path, env, prompt);
		else
			errexit("cd", "Absolute path too large.");
		return ;
	}
	if (*path == '/')
		tmp = ft_strdup(path);
	else
		tmp = ft_strstrjoin(cwd, "/", path);
	print_cd_error(tmp, path);
	free(tmp);
}

void	cd_tilde(char *str, t_env *env, char **prompt)
{
	char	*tmp;
	char	*tmp2;

	if (!(tmp = find_env(env, "HOME")))
	{
		errexit("cd", "HOME not set.");
		return ;
	}
	if (!str)
		tmp2 = ft_strdup(tmp);
	else
		tmp2 = ft_strjoin(tmp, str + 1);
	cd_current_dir(tmp2, env, prompt);
	free(tmp2);
}

void	cd(char **av, t_env *env, char **path)
{
	if (!*++av || (*av[0] == '~'))
		cd_tilde(*av, env, path);
	else if (*(av + 1))
		errexit("cd", "Too many arguments.");
	else if (!ft_strcmp(*av, "-") && find_env(env, "OLDPWD"))
		change_path(find_env(env, "OLDPWD"), env, path);
	else if (*av[0] == '/')
	{
		if (cd_path_validity(*av))
			change_path(*av, env, path);
		else
		{
			if (!lstat(*av, NULL))
				errexit("cd", "Not a directory.");
			else
				errexit("cd", "No such file or directory.");
		}
	}
	else
		cd_current_dir(*av, env, path);
}
