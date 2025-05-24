/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:05:14 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 07:25:00 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_shell.h"
#include <stdio.h>

/**
 * @brief Prints the environment variables.
 *
 * @param shell The shell instance.
 * @param args The arguments to the command.
 * 
 * @note This function prints the environment variables to the standard output.
 * It is used to display the current environment variables of the current shell.
 */
void	ft_env(t_shell *shell, char **args)
{
	(void)args;
	read_env(shell->env, NULL);
	shell->exit_code = 0;
}
