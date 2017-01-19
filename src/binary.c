/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 00:41:36 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/19 06:00:39 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
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
