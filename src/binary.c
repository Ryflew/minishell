/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 00:41:36 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/20 00:30:55 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "../include/minishell.h"

pid_t	g_father;

void	sig_hand(int sig)
{
	if (sig == SIGINT)
	{
		kill(g_father, sig);
		ft_putchar('\n');
	}
}

void	run_binary(char *path, char **av, t_env *env)
{
	char	**envi;

	g_father = fork();
	if (g_father > 0)
	{
		signal(SIGINT, sig_hand);
		wait(NULL);
		signal(SIGINT, SIG_DFL);
	}
	else if (g_father == 0)
	{
		envi = conv_env(env);
		execve(path, av, envi);
		if (envi)
			ft_strdelpp(&envi);
		exit(EXIT_SUCCESS);
	}
	g_father = -1;
	free(path);
}

char	current_binary(char **av, t_env *env)
{
	int		i;
	char	*str;
	char	*cwd;
	char	**tab;
	char	buff[4097];

	str = ft_strsub(*av, 2, ft_strlen(*av) - 2);
	i = -1;
	while (av[++i])
		;
	if (!(tab = (char**)malloc(sizeof(char*) * (i + 1))))
		exit(EXIT_FAILURE);
	if (!(cwd = getcwd(buff, 4097)))
		return (0);
	tab[0] = ft_strstrjoin(cwd, "/", str);
	free(str);
	i = 0;
	while (av[++i])
		tab[i] = ft_strdup(av[i]);
	tab[i] = NULL;
	i = is_absolute(tab, env);
	ft_strdelpp(&tab);
	return (i);
}

char	is_absolute(char **av, t_env *env)
{
	t_stat		file;

	if (**av && **av == '/')
	{
		if (!lstat(*av, &file) && S_ISREG(file.st_mode) && is_binary(*av) &&
			!access(*av, R_OK | X_OK))
		{
			run_binary(ft_strdup(*av), av, env);
			return (1);
		}
		else if (access(*av, F_OK) == -1)
		{
			errexit(*av, "No such file or directory.");
			return (1);
		}
		else if (access(*av, R_OK | X_OK) == -1)
		{
			errexit(*av, "Permission denied.");
			return (1);
		}
	}
	else if (**av && **av == '.' && *(*av + 1) && *(*av + 1) == '/')
		return (current_binary(av, env));
	return (0);
}
