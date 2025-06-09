/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:58:07 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 20:02:57 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_env.h"
#include "config.h"
#include "libft.h"

void set_default_env(t_env **env, char *current_path)
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
}
