/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 19:30:46 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/15 16:27:55 by vdarmaya         ###   ########.fr       */
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
void				echo(char **av, t_env *env);
void				run_binary(char *path, char **av, t_env *env);
void				del_all_env(t_env **list);
void				env_command(char **av, t_env *env);
void				cd(char **av, t_env *env);
char				*find_env(t_env *env, char *name);
char				**conv_env(t_env *env);
char				go_path(char **av, t_env *env);
t_env				*get_env(char **env);
t_env				*new_env(char *str);

#endif
