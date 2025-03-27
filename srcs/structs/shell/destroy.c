/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:43:19 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/13 19:23:25 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>
#include "env.h"

void	*destroy_shell(t_shell *shell)
{
	destroy_env(shell->env);
	free(shell->current_path);
	return (NULL);
}
