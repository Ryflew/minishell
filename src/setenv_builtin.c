/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 23:30:21 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/13 16:29:40 by vdarmaya         ###   ########.fr       */
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

void	set_env(char **av, t_env **env)
{
	char	*tmp;
	t_env	*first;

	if (setenv_size(av))
		return ;
	first = *env;
	if (!*++av)
	{
		print_env(*env);
		return ;
	}
	if (!(find_env(*env, *av)))
	{
		while ((*env)->next)
			*env = (*env)->next;
		if (!(*(av + 1)))
			tmp = ft_strjoin(*av, "=");
		else
			tmp = ft_strstrjoin(*av, "=", *(av + 1));
		(*env)->next = new_env(tmp);
		free(tmp);
	}
	else
		override_env(av, env);
	*env = first;
}