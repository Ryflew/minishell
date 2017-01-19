/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 19:30:46 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/19 23:45:11 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct		s_env
{

	char			*var_name;
	char			*var_content;
	char			*all;
	struct s_env	*next;

}					t_env;

void				go_core(char *command, t_env **env, char **path);
void				errexit(char *content, char *reason);
void				print_env(t_env *env);
void				set_env(char **av, t_env **env);
void				unset_env(char **av, t_env **env);
void				del_env(t_env *todel);
void				echo(char **av, t_env *env);
void				run_binary(char *path, char **av, t_env *env);
void				cd(char **av, t_env *env, char **path);
void				change_prompt(char *path, t_env *env);
void				print_usage(char invalid);
void				exit_command(char **av);
char				env_command(char **av, t_env *env);
char				is_absolute(char **av, t_env *env);
char				check_path(char *command, char *path);
char				go_path(char **av, t_env *env);
char				del_all_env(t_env **list);
char				is_binary(char *path);
char				cd_path_validity(char *path);
char				check_alpha(char *str);
char				*find_env(t_env *env, char *name);
char				*get_with_tilde(char *path, t_env *env);
char				**conv_env(t_env *env);
char				**clear_command(char *command, int j);
char				**next_command(char ***av, int *i, int *k);
t_env				*get_env(char **env);
t_env				*new_env(char *str);

#endif
