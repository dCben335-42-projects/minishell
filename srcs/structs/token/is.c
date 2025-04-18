/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:57 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 18:49:55 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"

t_bool	is_operator_token(t_token token)
{
	t_token_type	type;

	type = token.type;
	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR
		|| type == TOKEN_SEMICOL || type == TOKEN_BACKGROUND
		|| type == TOKEN_PIPE_ERR || type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT);
}
