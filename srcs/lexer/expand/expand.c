/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:10:10 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/17 19:14:26 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	*loop_tokens(t_dynarray *arr, t_shell *shell, void *(*f)(t_shell *, t_token *))
{
	t_uint	i;

	i = 0;
	while (i < arr->count)
	{
		if (!f(shell, arr->data[i]))
			return (NULL);
		i++;
	}
	return (arr);
}

static void	*expand_env(t_shell *shell, t_dynarray *tokens)
{
	return (loop_tokens(tokens, shell, &expand_env_token));
}

static void	*expand_wildcard(t_shell *shell, t_dynarray *tokens)
{
	return (loop_tokens(tokens, shell, &expand_wildcard_token));
}

/**
 * @brief Expands the tokens in the shell.
 *
 * @param shell The shell instance.
 * @param tokens The tokens to expand.
 * 
 * @return The expanded tokens or NULL if an error occurred.
 */
void	*expand(t_shell *shell, t_dynarray *tokens)
{
	if (!expand_env(shell, tokens))
		return (NULL);
	if (!expand_wildcard(shell, tokens))
		return (NULL);
	return (tokens);
}
