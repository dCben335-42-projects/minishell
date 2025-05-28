/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 02:50:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/28 20:34:07 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void debug_exitcode(t_shell *shell)
{
	if (shell->debug.all || shell->debug.exitcode)
	{
		printf(SECOND_COL"╔═══════════════════════════════════════╗\n");
   		printf("║\t"FIRST_COL"DEBUG MODE EXIT CODE: %3d"SECOND_COL"\t║\n", shell->exit_code);
    	printf("╚═══════════════════════════════════════╝"RESET_COL"\n");
	}
}

void debug_ast(t_shell *shell)
{
	if (shell->debug.all || shell->debug.ast)
	{
		printf(SECOND_COL"╔═══════════════════════════════════════╗\n");
   		printf("║\t"FIRST_COL"START DEBUG MODE AST JSON"SECOND_COL"\t║\n");
		printf("╚═══════════════════════════════════════╝"RESET_COL"\n");
		print_ast_json_wrapper(shell->ast->content);
		printf(SECOND_COL"╔═══════════════════════════════════════╗\n");
   		printf("║\t"FIRST_COL"END DEBUG MODE AST JSON"SECOND_COL"  \t║\n");
		printf("╚═══════════════════════════════════════╝"RESET_COL"\n");
	}
}

void debug_tokens(t_shell *shell, t_dynarray *tokens)
{
	if (shell->debug.all || shell->debug.tokens)
	{
		printf(SECOND_COL"╔═══════════════════════════════════════╗\n");
   		printf("║\t"FIRST_COL"START DEBUG MODE TOKENS"SECOND_COL"\t\t║\n");
		printf("╚═══════════════════════════════════════╝"RESET_COL"\n");
		print_tokens(tokens);
		printf(SECOND_COL"╔═══════════════════════════════════════╗\n");
   		printf("║\t"FIRST_COL"END DEBUG MODE TOKENS"SECOND_COL"  \t\t║\n");
		printf("╚═══════════════════════════════════════╝"RESET_COL"\n");
	}
}