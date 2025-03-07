/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:43:27 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/07 16:30:22 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "types.h"
# include <stddef.h>

typedef struct s_env {
    char			*key;
    char			*value;
    struct s_env	*prev;
	struct s_env	*next;
}	t_env;

t_env	*add_env(t_env **env, t_env *new);
t_env	*init_env(char *envp);
t_env	*find_env(t_env *env, char *key);
t_env	*replace_env(t_env *env, char *key, char *value);

char	*get_key_from_envp(char *envp);
char	*get_value_from_envp(char *envp);

void	*destroy_one_env(t_env *env);
void	*destroy_env(t_env *env);
void	read_env(t_env *env);

#endif