/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 19:32:42 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/13 21:35:51 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/get_next_line.h"
#include "../include/minishell.h"

int		main(int ac, char **av, char **sysenv)
{
	char	*command;
	t_env	*env;

	env = get_env(sysenv);
	(void)ac;
	(void)av;
	command = NULL;
	PROMPT
	while (get_next_line(0, &command))
	{
		if (ft_strlen(command) > 0)
			go_core(command, &env);
		free(command);
		command = NULL;
		PROMPT
	}
	return (0);
}
