/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:26:39 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 19:33:28 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"
#include "libft.h"

static t_bool	get_n_option(char *arg)
{
	if (!arg || !*arg || !*(arg + 1) || *arg != '-')
		return (FALSE);
	while (*(++arg) && *arg == 'n')
		;
	if (*arg)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Prints the arguments to the standard output.
 *
 * @param shell The shell instance.
 * @param args The arguments to print.
 * 
 * @note This function prints the arguments to the standard output
 * and adds a newline at the end if the -n option is not used.
 */
void	ft_echo(t_shell *shell, char **args)
{
	size_t	i;
	t_bool	is_n_option;

	i = 1;
	is_n_option = FALSE;
	while (args[i] && get_n_option(args[i]))
	{
		is_n_option = TRUE;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!is_n_option)
		ft_putchar_fd('\n', 1);
	shell->exit_code = 0;
}
