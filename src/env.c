/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 17:32:49 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/18 20:15:38 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/minishell.h"

t_env	*cpy_env(t_env *env)
{
	t_env	*elem;
	t_env	*first;

	first = NULL;
	if (env)
	{
		elem = new_env(env->all);
		first = elem;
		env = env->next;
	}
	while (env)
	{
		elem->next = new_env(env->all);
		elem = elem->next;
		env = env->next;
	}
	return (first);
}

void	add_new_var(char ***av, t_env **env)
{
	char	**new_av;
	int		i;

	if (**av[0] == '=')
	{
		errexit("env", "Invalid argument");
		return ;
	}
	i = 0;
	if (!(new_av = (char**)malloc(sizeof(char*) * 4)))
		exit(EXIT_FAILURE);
	new_av[0] = ft_strdup("unsetenv");
	new_av[1] = ft_strsub(**av, 0, ft_strchr(**av, '=') - **av);
	new_av[2] = ft_strdup(ft_strchr(**av, '=') + 1);
	new_av[3] = NULL;
	set_env(new_av, env);
	ft_strdelpp(&new_av);
}

void	env_command2(char **av, t_env **cpy)
{
	while (*av)
	{
		if (!ft_strcmp(*av, "-i"))
		{
			del_all_env(cpy);
			*cpy = NULL;
		}
		else if (!ft_strcmp(*av, "env"))
		{
			env_command(av, *cpy);
			break ;
		}
		else if (ft_strchr(*av, '='))
			add_new_var(&av, cpy);
		else
		{
			if (!go_path(av, *cpy))
				errexit("env", "PATH not set.");
			break ;
		}
		av++;
	}
}

void	env_command(char **av, t_env *env)
{
	t_env *cpy;

	if (!*++av)
		print_env(env);
	else
	{
		cpy = cpy_env(env);
		env_command2(av, &cpy);
		del_all_env(&cpy);
	}
}
