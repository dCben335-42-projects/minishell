/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:57 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/28 20:58:06 by abonneau         ###   ########.fr       */
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

int	is_text_token(t_token token)
{
	return (token.type & TOKEN_TEXT);
}

int	is_redir_token(t_token token)
{
	const t_token_type_flags	type = token.type;

	return ((type & E_REDIR_OPERATOR_MASK) > 0);
}
