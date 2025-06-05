/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:03:36 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/02 19:45:41 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/**
 * 
 * @brief Retrieves the next command node from the tokens.
 * 
 * @param args The AST global context containing the tokens.
 * 
 * @note If an allocation fails, it sets the "has_malloc_error" boolean to true.
 * 
 * @return 1 if a command node is found, 0 if empty or malloc error.
 * 
*/
t_bool	get_cmd(t_ast_ctx *args)
{
	args->local.cmd = &args->local.lcmd;
	get_cmd_primitive(args, &args->local.cmd);
	if (args->local.cmd)
		return (TRUE);
	args->i++;
	return (FALSE);
}

/**
 * 
 * @brief Checks if the current command node matches the given mask.
 * 
 * @param args The AST global context containing the current command node.
 * @param mask The mask to check against the command node type.
 * 
 * @return 1 if the command node matches the mask, 0 otherwise.
 * 
*/
int	is_cmd(t_ast_ctx *args, size_t mask)
{
	return (is_node(args->local.cmd, mask));
}
