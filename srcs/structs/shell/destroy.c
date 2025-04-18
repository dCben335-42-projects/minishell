/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:43:19 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 17:38:43 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_shell.h"
#include <stdlib.h>

void	*destroy_shell(t_shell *shell)
{
	destroy_env(shell->env);
	free(shell->current_path);
	return (NULL);
}
