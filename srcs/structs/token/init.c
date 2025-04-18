/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:16:15 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 18:42:28 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"
#include "libft.h"

t_token	*init_token(
	int token_type,
	const char *value,
	unsigned int start,
	size_t len
)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = token_type;
	token->value = ft_substr(value, start, len);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	return (token);
}
