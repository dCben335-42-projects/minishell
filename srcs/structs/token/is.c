/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:57 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/01 17:56:46 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"

int is_operator_token(t_token token)
{
	return (token.type & E_CONTROL_OPERATOR_MASK);
}

int	is_parenthesis_token(t_token token)
{
	return (token.type & E_PARENTHESIS_MASK);
}

int is_operator_ext_token(t_token token)
{
	return (token.type & E_CONTROL_OPERATOR_EXTENDED_MASK);
}

int	is_text_token(t_token token)
{
	return (token.type & E_TOKEN_NAME_MASK);
}

int	is_redir_token(t_token token)
{
	return (token.type & E_REDIR_OPERATOR_MASK);
}
