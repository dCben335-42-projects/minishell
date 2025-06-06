/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:40:57 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/06 03:30:11 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_ast.h"
#include "config.h"

/**
 * 
 * @brief Prints the AST in JSON format.
 * 
 * @param args The arguments containing the command and depth for printing.
 * 
*/
void	print_ast_cmd(t_ast_printer_ctx args)
{
	t_uint	i;
	t_ast	*node;

	if (!args.cmd)
		return ;
	i = 0;
	while (i < args.cmd->count)
	{
		node = (t_ast *)get_dynarray_value(args.cmd, i);
		print_ast_node(args, node, i == 0);
		i++;
	}
}

void	print_ast(t_dynarray *cmd)
{
	t_ast_printer_ctx	ctx;

	ctx = init_ast_printer_ctx(cmd, 2);
	printf("%s", ctx.v_l_hook);
	print_ast_cmd(ctx);
	printf("%s\n", ctx.v_r_hook);
}
