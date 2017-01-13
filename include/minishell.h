/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 19:30:46 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/13 16:44:17 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"

# define PROMPT ft_putstr("minishell> ");

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct		s_env
{

	char			*var_name;
	char			*var_content;
	char			*all;
	struct s_env	*next;

}					t_env;

void				go_core(char *command, t_env **env);
void				errexit(char *content, char *reason);
void				print_env(t_env *env);
void				set_env(char **av, t_env **env);
void				unset_env(char **av, t_env **env);
void				del_env(t_env *todel);
char				*find_env(t_env *env, char *name);
void				echo(char **av, t_env *env);
t_env				*get_env(char **env);
t_env				*new_env(char *str);

#endif
