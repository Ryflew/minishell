/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 23:16:02 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/18 18:23:41 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/minishell.h"

char	**end_return(char **tmp)
{
	char	**out;

	if (ft_strlen(*tmp) == 0)
	{
		free(*tmp);
		return (NULL);
	}
	out = ft_strsplit(*tmp, ' ');
	free(*tmp);
	return (out);
}

char	**have_semicolon(char **av, char **tmp, int *k, int *i)
{
	char	*tmp2;
	char	*tmp3;
	int		j;

	if (av[*k][*i] == ';')
	{
		++*i;
		return (end_return(tmp));
	}
	j = *i;
	while (*(av[*k] + *i) && (*(av[*k] + *i)) != ';')
		++*i;
	tmp2 = ft_strsub(av[*k], j, *i - j);
	tmp3 = *tmp;
	*tmp = ft_strstrjoin(tmp3, " ", tmp2);
	free(tmp3);
	free(tmp2);
	++*i;
	return (end_return(tmp));
}

char	**next_command(char ***argv, int *i, int *k)
{
	char	**av;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup("");
	av = *argv;
	while (av[*k])
	{
		if (ft_strchr(av[*k] + *i, ';'))
			return (have_semicolon(av, &tmp, k, i));
		else if (ft_strlen(av[*k] + *i) > 0)
		{
			tmp2 = tmp;
			tmp = ft_strstrjoin(tmp2, " ", av[*k] + *i);
			free(tmp2);
		}
		++*k;
		*i = 0;
	}
	return (end_return(&tmp));
}
