/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:26:39 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/05 16:02:08 by bcabocel         ###   ########.fr       */
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

void	ft_echo(t_shell *shell, char **args)
{
	size_t	i;
	t_bool	is_n_option;

	is_n_option = get_n_option(args[1]);
	i = is_n_option + 1;
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
