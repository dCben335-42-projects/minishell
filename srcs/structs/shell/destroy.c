/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:43:19 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 19:16:13 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_shell.h"
#include <stdlib.h>

/**
 * @brief Destroys the shell instance and frees the allocated memory.
 *
 * @param shell The shell instance to destroy.
 *
 * @return NULL
 *
 * @note This function frees the environment variables, the dynamic array,
 * the current path, and the abstract syntax tree.
 */
void	*destroy_shell(t_shell *shell)
{
	destroy_env(shell->env);
	destroy_dynarray(&shell->env_array);
	if (shell->ast)
		recursive_destroy_node(shell->ast);
	free(shell->current_path);
	return (NULL);
}
