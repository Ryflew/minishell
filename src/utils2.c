/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 00:35:15 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/21 00:43:21 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*clear_quot(char *str)
{
	int		i;
	int		count;
	char	*out;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] != '\"')
			++count;
	if (!(out = (char*)malloc(sizeof(char) * (count + 1))))
		exit(EXIT_FAILURE);
	i = -1;
	count = -1;
	while (str[++i])
		if (str[i] != '\"')
			out[++count] = str[i];
	out[++count] = '\0';
	return (out);
}
