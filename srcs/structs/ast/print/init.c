/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:05:53 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/06 03:30:26 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_ast.h"
#include "utils.h"
#include "config.h"

/**
 * 
 * @brief Initializes the context for printing the AST in JSON format.
 * 
 * @param cmd The dynamic array of command nodes to be printed.
 * 
*/
t_ast_printer_ctx	init_ast_printer_ctx(t_dynarray *cmd, t_uint depth)
{
	const t_ast_printer_ctx	ctx = {
		.cmd = cmd,
		.depth = depth,
		.v_l_brace = BRACE_COL"{\n"RESET_COL,
		.v_r_brace = BRACE_COL"}"RESET_COL,
		.v_l_hook = BRACE_COL"[\n"RESET_COL,
		.v_r_hook = BRACE_COL"]\n"RESET_COL,
		.v_content = FIRST_COL"\"content\": "RESET_COL,
		.f_type = FIRST_COL"\"type\": "SECOND_COL"\"%s\",\n"RESET_COL,
		.f_string = SECOND_COL"\"%s\"\n"RESET_COL
	};

	return (ctx);
}
