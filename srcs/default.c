/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 03:19:33 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 03:29:17 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_default_env(t_shell *shell)
{
	t_env *env = shell->env;

	if (!get_env_node(env, ENV_HOME_KEY))
		add_env_node(&env, init_env_node("HOME=/"));
	if (!get_env_node(env, ENV_USER_KEY))
		add_env_node(&env, init_env_node("USER=root"));
	if (!get_env_node(env, ENV_PATH_KEY))
		add_env_node(&env, init_env_node("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"));
	if (!get_env_node(env, ENV_PWD_KEY))
		add_env_node(&env, init_env_node("PWD=/"));
	if (!get_env_node(env, ENV_OLDPWD_KEY))
		add_env_node(&env, init_env_node("OLDPWD="));
}