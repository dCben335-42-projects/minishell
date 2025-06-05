/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:00:15 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/05 21:00:42 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "orchestrator.h"

/**
 * @brief Skips to the next command node in the AST.
 * 
 * @param node The command that has been handled.
 * 
 * @return The next command node or NULL if there are no more commands.
 */
t_ast_node	*skip_cmd(t_ast_node *node)
{
	t_ast_node	*next_node;

	next_node = node;
	while (!next_node->next)
	{
		if (next_node->parent == NULL)
			return (NULL);
		next_node = next_node->parent;
	}
	return (next_node->next);
}

/**
 * @brief Finds the next command node to execute in the AST.
 * 
 * @param node The command that has been handled.
 * 
 * @return The next command node to execute or NULL if there are
 * no more commands.
 */
t_ast_node	*find_next_cmd(t_ast_node *node)
{
	t_ast_node	*child;

	if (node == NULL)
		return (NULL);
	if (!node->content)
		return (skip_cmd(node));
	child = get_dynarray_value(node->content, 0);
	if (child && is_valid_exec_type(child->type))
		return (child);
	return (skip_cmd(node));
}
