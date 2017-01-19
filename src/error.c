/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 22:29:19 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/19 22:29:43 by vdarmaya         ###   ########.fr       */
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

void	print_usage(char invalid)
{
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putchar_fd(invalid, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: env [-i] [-u name] [name=value ...]", 2);
	ft_putendl_fd("           [utility [argument ...]]", 2);
}
