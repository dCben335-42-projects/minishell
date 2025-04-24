/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:57 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 20:14:20 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"

int is_operator_token(t_token token)
{
	const t_token_type_flags	type = token.type;

	return ((type & E_CONTROL_OPERATOR_MASK) > 0);
}

int	is_parenthesis_token(t_token token)
{
	const t_token_type_flags	type = token.type;

	return ((type & E_PARENTHESIS_MASK) > 0);
}

/* t_bool	is_text_token(t_token token)
{
	const t_token_type	type = token.type;

	return (type == TOKEN_TEXT || type == TOKEN_VAR_TEXT
		|| type == TOKEN_LITERAL_TEXT);
} */

int	is_redir_token(t_token token)
{
	const t_token_type_flags	type = token.type;

	return ((type & E_REDIR_OPERATOR_MASK) > 0);
}
