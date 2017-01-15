/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 00:41:36 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/14 15:24:34 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../include/minishell.h"

void	run_binary(char *path, char **av, t_env *env)
{
	pid_t	father;
	char	**envi;

	father = fork();
	if (father > 0)
		wait(NULL);
	else if (father == 0)
	{
		envi = conv_env(env);
		execve(path, av, envi);
		if (envi)
			ft_strdelpp(&envi);
		exit(EXIT_SUCCESS);
	}
	free(path);
}
