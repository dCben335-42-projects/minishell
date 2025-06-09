/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:40:57 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 18:51:16 by bcabocel         ###   ########.fr       */
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

/**
 * 
 * @brief Prints the AST in JSON format.
 * 
 * @param cmd The dynamic array of command nodes to be printed.
 * @param depth The current depth in the AST, used for indentation.
 * 
*/
void	print_ast(t_dynarray *cmd)
{
	t_ast_printer_ctx	ctx;

	ctx = init_ast_printer_ctx(cmd, 2);
	ft_putstr_fd(ctx.v_l_hook, 1);
	print_ast_cmd(ctx);
	ft_putendl_fd(ctx.v_r_hook, 1);
}
