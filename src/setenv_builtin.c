/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 23:30:21 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/15 17:15:22 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/minishell.h"

void	override_env(char **av, t_env **env)
{
	while (ft_strcmp((*env)->var_name, *av) != 0)
		*env = (*env)->next;
	free((*env)->var_content);
	free((*env)->all);
	if (!*++av)
		(*env)->var_content = ft_strdup("");
	else
		(*env)->var_content = ft_strdup(*av);
	(*env)->all = ft_strstrjoin((*env)->var_name, "=", (*env)->var_content);
}

char	setenv_size(char **av)
{
	int		i;

	i = 0;
	while (av[i] && i < 4)
		++i;
	if (i == 4)
	{
		errexit("setenv", "Too many arguments.");
		return (1);
	}
	return (0);
}

char	*get_tmp(char **av)
{
	if (!(*(av + 1)))
		return (ft_strjoin(*av, "="));
	else
		return (ft_strstrjoin(*av, "=", *(av + 1)));
}

void	set_env(char **av, t_env **env)
{
	char	*tmp;
	t_env	*first;

	if (setenv_size(av))
		return ;
	first = *env;
	if (!*++av)
		print_env(*env);
	else if (!(find_env(*env, *av)))
	{
		while (*env && (*env)->next)
			*env = (*env)->next;
		tmp = get_tmp(av);
		if (!*env)
			*env = new_env(tmp);
		else
			(*env)->next = new_env(tmp);
		free(tmp);
	}
	else
		override_env(av, env);
	if (first)
		*env = first;
}
