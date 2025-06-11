/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:58:07 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/11 02:17:19 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_env.h"
#include "config.h"
#include "libft.h"

/**
 * 
 * @brief Sets the default environment variables.
 * 
 * This function initializes the environment with default values
 * for PATH, PWD, and OLDPWD if they are not already set.
 * 
 * @param env Pointer to the environment structure.
 * @param current_path The current working directory to set as PWD.
 * 
*/
void	set_default_env(t_env **env, char *current_path)
{
	char	*pwd;

	if (!get_env_node(*env, ENV_PATH_KEY))
		add_env_node(env, init_env_node(ENV_PATH_KEY"="DEFAULT_PATH));
	if (!get_env_node(*env, ENV_PWD_KEY) && current_path)
	{
		pwd = ft_strjoin(ENV_PWD_KEY"=", current_path);
		if (pwd)
			add_env_node(env, init_env_node(pwd));
		free(pwd);
	}
	if (!get_env_node(*env, ENV_OLDPWD_KEY))
		add_env_node(env, init_env_node(ENV_OLDPWD_KEY"="""));
	if (!get_env_node(*env, ENV_SHLVL_KEY))
		add_env_node(env, init_env_node(ENV_SHLVL_KEY"=""1"));
}
