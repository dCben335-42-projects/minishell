/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:05:23 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/02 19:51:10 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <stdlib.h>

/**
 * @brief Builds the AST from the given tokens.
 * This function initializes the master node of the AST and
 * calls the command master function to populate it.
 * 
 * @param tokens Dynamic array of tokens.
 * 
 * @note The master node is initialized with the type CMD_SEQ.
 * 
 * @return t_ast_node* Pointer to the root of the AST or NULL on malloc error.
 */
t_ast_node	*ast_builder(t_dynarray *tokens)
{
	t_ast_ctx	ast_glbctx;
	t_ast_node		*master_node;

	master_node = init_node(CMD_SEQ, NULL);
	if (!master_node)
		return (NULL);
	ast_glbctx = init_ast_glbctx(
			tokens,
			0,
			tokens->count - 1,
			master_node);
	add_master_cmds(&ast_glbctx);
	if (ast_glbctx.local.cmd_master && ast_glbctx.has_malloc_error)
		recursive_destroy_node(ast_glbctx.local.cmd_master);
	return (ast_glbctx.local.cmd_master);
}
