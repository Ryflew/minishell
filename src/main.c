/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 19:32:42 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/15 23:27:27 by vdarmaya         ###   ########.fr       */
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
	PROMPT
	while (get_next_line(0, &command))
	{
		if (ft_strlen(command) > 0)
			go_core(command, &env);
		free(command);
		PROMPT
	}
	return (0);
}

/*
** TODO :
** - Verification si il y a que des espaces ou des tab dans l'entrée standard
**
**	BONUS:
** - gestion des signaux (CTRL-C)...
** - Faire la verification si les fichier dans PATH sont bien des binaires
** - La completion
** - Séparation par un ';'
** - cd ~
** - Mettre le path dans le prompt
*/