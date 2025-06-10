/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:00:29 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/10 03:33:42 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_ast.h"

static const t_convert_map	*get_token_to_cmd_map(void)
{
	static const t_convert_map	map[] = {
	{TEXT,					CMD_TEXT},
	{QUOTED_TEXT,			CMD_QUOTED_TEXT},
	{ENV,				CMD_EXPAND},
	{QUOTED_EXPAND,			CMD_QUOTED_EXPAND},
	{WILDCARD,				CMD_WILDCARD},
	{OP_OR,					CMD_OR},
	{OP_AND,				CMD_AND},
	{OP_SEMICOL,			CMD_SEMICOL},
	{OP_PIPE,				CMD_PIPE},
	{OP_PARENTHESIS_OPEN,	CMD_PARENTHESIS_OPEN},
	{OP_PARENTHESIS_CLOSE,	CMD_PARENTHESIS_CLOSE},
	{R_IN,					CMD_REDIR_IN},
	{R_OUT,					CMD_REDIR_OUT},
	{R_APPEND,				CMD_APPEND},
	{R_HEREDOC_TRIM,		CMD_HEREDOC_TRIM},
	{R_HEREDOC,				CMD_HEREDOC},
	{0,						0},
	};

	return (map);
}

/**
 * 
 * @brief Converts a token to a command node.
 * 
 * @param token The token to be converted.
 * 
 * @return t_ast* Pointer to the command node
 * or NULL if the token is not recognized or if it is NULL
 * or if an malloc fail.
 * 
*/
t_ast	*convert_token_to_ast(t_token *token)
{
	const t_convert_map	*map = get_token_to_cmd_map();

	if (!token)
		return (NULL);
	while (map->type)
	{
		if (map->type == token->type)
		{
			if (is_text_token(token))
				return (init_ast_node(map->cmd, token->value));
			return (init_ast_node(map->cmd, NULL));
		}
		map++;
	}
	return (NULL);
}
