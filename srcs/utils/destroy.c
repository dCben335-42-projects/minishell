/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:39:46 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/15 20:42:34 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_shell.h"
#include "utils.h"
#include "libft.h"

/**
 * @brief Destroy the current process and free the allocated memory.
 * 
 * @param shell The shell instance.
 * @param argv The command and its arguments with the first
 * argument being the command itself.
 * 
 * @note This dunction can also be used to free the arguments and
 * destroy the shell instance.
 * 
 * @return NULL
 */
void	*destroy_self(t_shell *shell, char **argv, int exit_code)
{
	if (argv)
		ft_free_split(argv);
	destroy_shell(shell);
	close_fds(0);
	exit(exit_code);
	return (NULL);
}