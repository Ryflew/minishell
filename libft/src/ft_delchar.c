/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 16:56:39 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/16 17:23:00 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/libft.h"

char	*ft_delchar(char *str, int c)
{
	char	*out;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != c)
			++j;
	}
	if (!j)
		return (ft_strdup(""));
	if (i == j)
		return (ft_strdup(str));
	if (!(out = (char*)malloc(sizeof(char) * (j + 1))))
		exit(EXIT_FAILURE);
	out[j] = '\0';
	i = -1;
	while (*str)
	{
		if (*str != c)
			out[++i] = *str;
		++str;
	}
	return (out);
}