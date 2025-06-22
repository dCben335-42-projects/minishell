/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:05:23 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/22 15:39:30 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_builder.h"
#include <stdlib.h>
#include "config.h"
#include "libft.h"

/**
 * 
 * @brief Builds the AST from the given tokens.
 * This function initializes the master sub of the AST and
 * calls the command master function to populate it.
 * 
 * @param tokens Dynamic array of tokens.
 * 
 * @note The master sub is initialized with the type CMD_SEQ.
 * 
 * @return t_ast* Pointer to the root of the AST or NULL on malloc error.
 * 
*/
t_ast	*ast_builder(t_dynarray *tokens)
{
	t_ast_ctx	ast_glbctx;
	t_ast		*master_node;

	master_node = init_ast_node(CMD_SEQ, NULL);
	if (!master_node)
	{
		ft_putendl_fd(ERR_MALLOC, 2);
		return (NULL);
	}
	ast_glbctx = init_ast_glbctx(
			tokens,
			0,
			tokens->count - 1,
			master_node);
	add_master_cmds(&ast_glbctx);
	if (ast_glbctx.has_malloc_error)
		ft_putendl_fd(ERR_MALLOC, 2);
	if (ast_glbctx.local.cmd_master && ast_glbctx.has_malloc_error)
		return (destroy_ast(ast_glbctx.local.cmd_master));
	return (ast_glbctx.local.cmd_master);
}
