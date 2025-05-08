/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:10:10 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/08 16:46:17 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"

static void	*loop_args(
	t_dynarray *arr,
	t_shell *shell,
	void *(*f)(t_shell *, char **)
)
{
	t_uint	i;

	i = 0;
	while (i < arr->count)
	{
		if (!f(shell, (char **)&arr->data[i]))
			return (NULL);
		i++;
	}
	return (arr);
}

static void	*expand_env(t_shell *shell, t_dynarray *args)
{
	return (loop_args(args, shell, &expand_env_token));
}

static void	*expand_wildcard(t_shell *shell, t_dynarray *args)
{
	return (loop_args(args, shell, &expand_wildcard_token));
}

/**
 * @brief Expands the tokens in the shell.
 *
 * @param shell The shell instance.
 * @param tokens The tokens to expand.
 * 
 * @return The expanded tokens or NULL if an error occurred.
 */
void	*expand(t_shell *shell, t_dynarray *args)
{
	if (!expand_env(shell, args))
		return (destroy_dynarray(args));
	if (!expand_wildcard(shell, args))
		return (destroy_dynarray(args));
	return (args);
}
