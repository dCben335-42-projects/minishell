/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:53:27 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 20:56:14 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"
#include "struct_shell.h"

static void	skip_redirection(t_uint *i, t_uint count, t_dynarray *arr)
{
	t_ast	*node;

	while (*i < count)
	{
		node = (t_ast *)get_dynarray_value(arr, *i);
		if (!is_redirection(node->type))
			break ;
		(*i)++;
	}
}

/**
 * @brief Converts a command represented by a dynamic array of AST nodes
 * into an argument vector (argv) for execution.
 *
 * @param shell The shell instance containing the environment and state.
 * @param arr The dynamic array containing the AST nodes representing the command.
 * @param argv The dynamic array to store the resulting arguments.
 * 
 * @note This function processes each AST node in the command,
 * skipping any redirection nodes, and expands the content of each node
 * into the argument vector. 
 *
 * @return A pointer to the dynamic array containing the arguments, or NULL if an error occurs.
 */
t_dynarray	*cmd_to_argv(t_shell *shell, t_dynarray *arr, t_dynarray *argv)
{
	t_ast	*node;
	t_uint		i;

	if (!argv->data)
		return (NULL);
	i = 0;
	while (i < arr->count)
	{
		skip_redirection(&i, arr->count, arr);
		node = (t_ast *)get_dynarray_value(arr, i);
		if (node && !expand_word(shell, node->content, argv))
			return (destroy_dynarray(argv));
		i++;
	}
	return (argv);
}
