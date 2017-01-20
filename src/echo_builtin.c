/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 22:04:04 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/21 00:11:35 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo_env(char *str, t_env *env, char nflag)
{
	char	*tmp;

	if (!(tmp = find_env(env, str + 1)))
		errexit(str + 1, "Undefined variable.");
	else
	{
		if (nflag)
			ft_putstr(tmp);
		else
			ft_putendl(tmp);
	}
}

void	echo(char **av, t_env *env)
{
	char	nflag;

	if (*++av && !ft_strcmp(*av, "-n") && (++av || !av))
		nflag = 1;
	else
		nflag = 0;
	if (!*av && !nflag)
		ft_putchar('\n');
	while (*av)
	{
		if (*av[0] == '$')
			echo_env(*av, env, nflag);
		else
		{
			if (!(*(av + 1)) && !nflag)
				ft_putendl(*av);
			else
			{
				ft_putstr(*av);
				if (*(av + 1))
					ft_putchar(' ');
			}
		}
		++av;
	}
}
