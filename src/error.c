/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 22:29:19 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/14 00:11:11 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/minishell.h"

void	errexit(char *content, char *reason)
{
	ft_putstr_fd(content, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(reason, 2);
}
