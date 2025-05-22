/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:57 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 18:48:34 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"

int is_control_token(t_token token)
{
	return (token.type & get_lexer_token_def()->masks.control);
}

int	is_parenthesis_token(t_token token)
{
	return (token.type & get_lexer_token_def()->masks.paren);
}

int is_control_extended_token(t_token token)
{
	return (token.type & get_lexer_token_def()->masks.control_extended);
}

int	is_text_token(t_token token)
{
	return (token.type & get_lexer_token_def()->masks.text);
}

int	is_redir_token(t_token token)
{
	return (token.type & get_lexer_token_def()->masks.redir);
}

int	is_meta_token(t_token token)
{
	return (token.type & get_lexer_token_def()->masks.metachar);
}