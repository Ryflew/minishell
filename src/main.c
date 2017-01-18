/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 19:32:42 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/18 19:43:45 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../include/get_next_line.h"
#include "../include/minishell.h"

void	get_current_path(char **prompt, t_env *env)
{
	char	*cwd;
	char	buff[4097];

	cwd = getcwd(buff, 4097);
	*prompt = get_with_tilde(cwd, env);
}

void	print_prompt(char *path)
{
	ft_putstr("[minishell:");
	ft_putstr(path);
	ft_putstr("] $> ");
}

int		main(int ac, char **av, char **sysenv)
{
	char	*command;
	char	*path;
	t_env	*env;

	env = get_env(sysenv);
	get_current_path(&path, env);
	(void)ac;
	(void)av;
	print_prompt(path);
	while (get_next_line(0, &command))
	{
		if (ft_strlen(command) > 0)
			go_core(command, &env, &path);
		free(command);
		print_prompt(path);
	}
	return (0);
}

/*
** TODO :
**	BONUS:
** - Gestion des signaux (CTRL-C...)
** - La completion -> je pense osef
*/