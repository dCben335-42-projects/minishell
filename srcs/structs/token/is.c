/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:57 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/14 19:59:54 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"

int is_operator_token(t_token token)
{
	return (token.type & get_lexer_token_def()->masks.control);
}

int	is_parenthesis_token(t_token token)
{
	return (token.type & get_lexer_token_def()->masks.paren);
}

int is_operator_ext_token(t_token token)
{
	return (token.type & get_lexer_token_def()->masks.extended);
}

int	is_text_token(t_token token)
{
	return (token.type & get_lexer_token_def()->masks.name);
}

int	is_redir_token(t_token token)
{
	return (token.type & get_lexer_token_def()->masks.redir);
}
