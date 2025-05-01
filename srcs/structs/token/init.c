/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:16:15 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/01 23:06:50 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"
#include "libft.h"

t_token	*init_token(
	int token_type,
	const char *start,
	size_t len
)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = token_type;
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
