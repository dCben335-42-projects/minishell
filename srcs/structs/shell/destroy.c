/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:43:19 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/06 18:45:56 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_shell.h"
#include <stdlib.h>

void	*destroy_shell(t_shell *shell)
{
	destroy_env(shell->env);
	destroy_dynarray(&shell->env_array);
	if (shell->ast)
		destroy_dynarray(shell->ast);
	free(shell->current_path);
	return (NULL);
}
