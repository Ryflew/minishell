/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:10:16 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/13 00:43:28 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*get_env(char **env)
{
	t_env	*first;
	t_env	*elem;

	if (*env)
	{
		first = new_env(*env);
		elem = first;
	}
	while (++env && *env)
	{
		elem->next = new_env(*env);
		elem = elem->next;
	}
	return (first);
}

char	*find_env(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->var_name, name))
			return (env->var_content);
		env = env->next;
	}
	return (NULL);

}

void	print_env(t_env *env)
{
	while (env)
	{
		ft_putendl(env->all);
		env = env->next;
	}
}
