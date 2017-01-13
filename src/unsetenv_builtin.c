/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 15:59:25 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/13 23:57:01 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/minishell.h"

void	unset_env(char **av, t_env **env)
{
	t_env	*first;
	t_env	*prev;

	if (!*++av)
		errexit("unsetenv", "Too few arguments.");
	first = *env;
	while (*av)
	{
		prev = *env;
		while (*env && ft_strcmp((*env)->var_name, *av))
		{
			prev = *env;
			*env = (*env)->next;
		}
		if (*env && !ft_strcmp(prev->var_name, (*env)->var_name))
			first = first->next;
		else if (*env)
			prev->next = (*env)->next;
		if (*env)
			del_env(*env);
		*env = first;
		av++;
	}
}
