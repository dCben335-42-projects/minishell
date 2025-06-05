/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:43:27 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 21:57:02 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_ENV_H
# define STRUCT_ENV_H

# include "libft_tree.h"
# include "struct_dynarray.h"

typedef t_tree	t_env;

# define ENV_HOME_KEY "HOME"
# define ENV_USER_KEY "USER"
# define ENV_PATH_KEY "PATH"
# define ENV_PWD_KEY "PWD"
# define ENV_OLDPWD_KEY "OLDPWD"

t_env		*init_env(char **envp);
t_env		*init_env_node(char *envp);

void		*destroy_env(t_env *env);
void		*destroy_env_node(t_env **env, t_env *node);

t_env		*add_env_node(t_env **env, t_env *new);
t_env		*add_existing_env(t_env *env, char *key, char *value);

size_t		parse_env_key_len(const char *str);
char		*parse_env_key(char *envp);
char		*parse_env_value(char *envp);

t_env		*get_env_node(t_env *env, char *key);
t_env		*get_parent_node(t_env *env, t_env *node);
size_t		get_size_env(t_env *env);

void		read_env(t_env *env, t_bool for_export);

t_dynarray	env_to_array(t_env *env);

#endif