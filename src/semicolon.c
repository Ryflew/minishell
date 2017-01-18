/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 23:16:02 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/18 06:08:18 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/minishell.h"

char	**next_command(char ***argv, int *i, int *k)
{
	int		j;
	char	**av;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	**out;

	tmp = ft_strdup("");
	av = *argv;
	while (av[*k])
	{
		if (ft_strchr(av[*k] + *i, ';'))
		{
			if (av[*k][*i] == ';')
			{
				++*i;
				if (ft_strlen(tmp) == 0)
				{
					free(tmp);
					return (NULL);
				}
				out = ft_strsplit(tmp, ' ');
				free(tmp);
				return (out);
			}
			j = *i;
			while (*(av[*k] + *i) && (*(av[*k] + *i)) != ';')
				++*i;
			tmp2 = ft_strsub(av[*k], j, *i - j);
			tmp3 = tmp;
			tmp = ft_strstrjoin(tmp3, " ", tmp2);
			free(tmp3);
			free(tmp2);
			++*i;
			out = ft_strsplit(tmp, ' ');
			free(tmp);
			return (out);
		}
		else if (ft_strlen(av[*k] + *i) > 0)
		{
			tmp2 = tmp;
			tmp = ft_strstrjoin(tmp2, " ", av[*k] + *i);
			free(tmp2);
		}
		++*k;
		*i = 0;
	}
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		return (NULL);
	}
	out = ft_strsplit(tmp, ' ');
	free(tmp);
	return (out);
}
