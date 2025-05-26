/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:16:15 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 08:02:51 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"
#include "libft.h"

/**
 * @brief Initializes a token structure with the given type, start position,
 * and length.
 *
 * @param token_type The type of the token.
 * @param start A string pointer to the start position of the token.
 * @param len The length of the token value.
 * 
 * @return A pointer to the initialized token structure.
 *
 * @note This function allocates memory for a new token structure,
 * sets its type, * rules, and value based on the provided parameters.
 * If memory allocation * fails, it returns NULL.
 */
t_token	*init_token(t_token_type token_type, const char *start, size_t len)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = token_type;
	token->rules = get_token_rules(token_type);
	if (len != 0)
		token->value = ft_substr(start, 0, len);
	else
		token->value = ft_strdup("");
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	return (token);
}
