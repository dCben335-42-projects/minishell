/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 02:50:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 03:10:36 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "config.h"

void	debug_exitcode(t_shell *shell)
{
	if (!shell->debug.exitcode && !shell->debug.all)
		return ;
	ft_putendl_fd(SECOND_COL"╔═══════════════════════════════════════╗", 1);
	printf("║\t"FIRST_COL"DEBUG MODE EXIT CODE: %3d"SECOND_COL"\t║\n",
		shell->exit_code);
	ft_putendl_fd("╚═══════════════════════════════════════╝"RESET_COL, 1);
}

void	debug_ast(t_shell *shell)
{
	if (!shell->debug.ast && !shell->debug.all)
		return ;
	ft_putendl_fd(SECOND_COL"╔═══════════════════════════════════════╗", 1);
	ft_putendl_fd("║\t"FIRST_COL"START DEBUG MODE AST JSON"SECOND_COL"\t║", 1);
	ft_putendl_fd("╚═══════════════════════════════════════╝"RESET_COL"", 1);
	print_ast(shell->ast->content);
	ft_putendl_fd(SECOND_COL"╔═══════════════════════════════════════╗", 1);
	ft_putendl_fd("║\t"FIRST_COL"END DEBUG MODE AST JSON"SECOND_COL"  \t║", 1);
	ft_putendl_fd("╚═══════════════════════════════════════╝"RESET_COL, 1);
}

void	debug_tokens(t_shell *shell, t_dynarray *tokens)
{
	if (!shell->debug.tokens && !shell->debug.all)
		return ;
	ft_putendl_fd(SECOND_COL"╔═══════════════════════════════════════╗", 1);
	ft_putendl_fd("║\t"FIRST_COL"START DEBUG MODE TOKENS"SECOND_COL"\t\t║", 1);
	ft_putendl_fd("╚═══════════════════════════════════════╝"RESET_COL, 1);
	print_tokens(tokens);
	ft_putendl_fd(SECOND_COL"╔═══════════════════════════════════════╗", 1);
	ft_putendl_fd("║\t"FIRST_COL"END DEBUG MODE TOKENS"SECOND_COL"  \t\t║", 1);
	ft_putendl_fd("╚═══════════════════════════════════════╝"RESET_COL, 1);
}
