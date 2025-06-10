/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:58:42 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 01:39:17 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_env.h"
#include "libft_math.h"
#include "libft.h"

static t_bool	ft_is_only_one_number(const char *str)
{
	t_bool	is_space_between;

	while (ft_isspace(*str))
		str++;
	is_space_between = FALSE;
	while (*str)
	{
		if (ft_isspace(*str))
		{
			is_space_between = TRUE;
			while (ft_isspace(*str))
				str++;
			continue ;
		}
		else if (!ft_isdigit(*str) || is_space_between)
			return (FALSE);
		str++;
	}
	return (TRUE);
}

/**
 * 
 * @brief Updates the SHLVL environment variable.
 * 
 * This function increments the SHLVL variable by 1.
 * If SHLVL is not set or is not a valid number, it initializes it to 1.
 * 
 * @param env Pointer to the environment structure.
 * 
 */
void	update_env_shlvl(t_env **env)
{
	t_env	*shlvl_node;
	char	*new_val;
	int		shlvl;

	shlvl_node = get_env_node(*env, ENV_SHLVL_KEY);
	if (!shlvl_node)
		return ;
	shlvl = 1;
	if (shlvl_node->value && ft_is_only_one_number(shlvl_node->value))
		shlvl += ft_atoi_base(shlvl_node->value, BASE_10);
	new_val = ft_itoa_base(shlvl, BASE_10);
	if (!new_val)
		return ;
	free(shlvl_node->value);
	shlvl_node->value = new_val;
}
