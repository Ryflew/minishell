/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 21:47:16 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/15 15:59:03 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/minishell.h"

t_env	*new_env(char *str)
{
	t_env	*elem;
	char	*tmp;

	if (!(elem = (t_env*)malloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	elem->all = ft_strdup(str);
	elem->var_name = ft_strsub(str, 0, ft_strchr(str, '=') - str);
	tmp = ft_strchr(str, '=') + 1;
	if (!*tmp)
		elem->var_content = ft_strdup("");
	else
		elem->var_content = ft_strdup(tmp);
	elem->next = NULL;
	return (elem);
}

void	del_env(t_env *todel)
{
	free(todel->var_name);
	free(todel->var_content);
	free(todel->all);
	free(todel);
}

void	del_all_env(t_env **list)
{
	t_env	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		del_env(*list);
		*list = tmp;
	}
}