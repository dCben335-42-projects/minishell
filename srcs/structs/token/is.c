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

t_bool	is_operator_token(t_token token)
{
	const t_token_type	type = token.type;

	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR
		|| type == TOKEN_SEMICOL || type == TOKEN_BACKGROUND
		|| type == TOKEN_PIPE_ERR);
}

t_bool	is_parenthesis_token(t_token token)
{
	const t_token_type	type = token.type;

	return (type == TOKEN_OPEN_BRACKET || type == TOKEN_CLOSE_BRACKET);
}

t_bool	is_text_token(t_token token)
{
	const t_token_type	type = token.type;

	return (type == TOKEN_TEXT || type == TOKEN_VAR_TEXT
		|| type == TOKEN_LITERAL_TEXT);
}

t_bool	is_redir_token(t_token token)
{
	const t_token_type	type = token.type;

	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}
