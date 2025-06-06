/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:03:36 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/06 03:09:49 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_builder.h"

/**
 * 
 * @brief Adds the child node to the contents of the parent node.
 * 
 * @param parent The parent node to which the child node will be added.
 * @param child The child node to be added.
 * @param args The arguments structure containing the malloc error flag.
 * 
 * @note If the allocation fails, it sets the "has_malloc_error" boolean to true.
 *
*/
void	add_child(t_ast *parent,
	t_ast **child, t_ast_ctx *args)
{
	if (!*child)
		return ;
	if (!add_ast_child_primitive(parent, *child))
	{
		args->has_malloc_error = TRUE;
		return ;
	}
	*child = NULL;
}

/**
 * 
 * @brief Retrieves the next command node from the tokens.
 * 
 * @param args The AST global context containing the tokens.
 * 
 * @note If an allocation fails, it sets the "has_malloc_error" boolean to true.
 * @note It increments the index (args->i) when it returns FALSE.
 * 
 * @return TRUE if a command node is found, otherwise FALSE 
 * (malloc error or empty cmd).
 * 
*/
t_bool	get_cmd(t_ast_ctx *args)
{
	args->local.cmd = &args->local.lcmd;
	add_cmd_primitive(args, &args->local.cmd);
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
	return (is_ast_types(args->local.cmd, mask));
}
