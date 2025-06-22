/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:58:30 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/21 16:51:30 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_builder.h"

/**
 * 
 * @brief Converts a token to a command node.
 * 
 * @param token The token to be converted.
 * @param args The AST global context for error handling.
 * 
 * @note If an allocation fails, it sets the "has_malloc_error" boolean to true.
 * 
 * @return t_ast* Pointer to the command node or NULL on malloc error.
 * 
*/
t_ast	*ast_convert_token_to_cmd(t_ast_ctx *args, t_token *token)
{
	t_ast	*node;

	node = convert_token_to_ast(token);
	if (!node)
	{
		args->has_malloc_error = TRUE;
		return (NULL);
	}
	return (node);
}

/**
 * 
 * @brief Initializes a new AST node with the given type and value.
 * 
 * @param type The type of the node to be initialized.
 * @param args The AST global context for error handling.
 * 
 * @note If an allocation fails, it sets the "has_malloc_error" boolean to true.
 * 
 * @return t_ast* Pointer to the initialized node or NULL on malloc error.
 * 
*/
t_ast	*ast_init_node(t_ast_ctx *args, t_node_type type)
{
	t_ast	*node;

	node = init_ast_node(type, NULL);
	if (!node)
	{
		args->has_malloc_error = TRUE;
		return (NULL);
	}
	return (node);
}

/**
 * 
 * @brief Initializes the t_ast_ctx structure with the given parameters.
 * 
 * @param tokens The dynamic array of tokens.
 * @param start The starting index in the tokens array.
 * @param end The ending index in the tokens array.
 * @param cmd_master The command master node to be initialized.
 * 
 * @return t_ast_ctx initialized structure with the provided parameters.
 * 
*/
t_ast_ctx	init_ast_glbctx(
	t_dynarray *tokens,
	t_uint start,
	t_uint end,
	t_ast *cmd_master
)
{
	t_ast_ctx	args;

	args.tokens = tokens;
	args.start = start;
	args.i = start;
	args.end = end;
	args.local.cmd_master = cmd_master;
	args.has_malloc_error = FALSE;
	return (args);
}

/**
 * @brief Checks if a malloc error occurred and sets the output node.
 * 
 * @param node The AST node to check for malloc error.
 * @param out Pointer to fill with the pointer node if no error occurred.
 * 
 * @return t_bool TRUE if a malloc error occurred, FALSE otherwise.
 * 
*/
t_bool	ast_merr(t_ast *node, t_ast **out)
{
	if (!node)
		return (TRUE);
	*out = node;
	return (FALSE);
}

/**
 * @brief Checks if the current command node is empty.
 * 
 * @param args The AST global context containing the tokens and indices.
 * 
 * @return t_bool TRUE if the command node is empty, FALSE otherwise.
*/
t_bool	is_empty(t_ast_ctx *args)
{
	t_token	*token;

	token = get_dynarray_value(args->tokens, args->i);
	if (token->type == M_SPACE)
		token = get_dynarray_value(args->tokens, args->i + 1);
	if (token->type == M_EOF)
		return (TRUE);
	if (is_control_extended_token(token))
		return (TRUE);
	return (FALSE);
}
