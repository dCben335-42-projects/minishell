/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:36:44 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/21 21:19:18 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_builder.h"

t_ast	*get_adjacent_cmd(t_ast_ctx *args, int count, t_bool is_redir)
{
	t_token		*token;

	if (args->has_malloc_error)
		return (NULL);
	token = get_dynarray_value(args->tokens, args->i + count + 1);
	if (token && token->type & M_SPACE)
		token = get_dynarray_value(args->tokens, args->i + count + 2);
	if (is_redir)
	{
		if (token && is_redir_token(token))
			return (ast_init_node(args, CMD_SUB_REDIR));
		return (NULL);
	}
	if (token && token->type & OP_PIPE)
		return (ast_init_node(args, CMD_PIPE));
	return (NULL);
}

static int	count_token_between_brackets(t_dynarray *tokens, t_uint i)
{
	int			count;
	t_bracket	parenthesis;
	t_token		*token;

	count = 0;
	parenthesis = (t_bracket){1, 0};
	while (i < tokens->count - 1)
	{
		token = get_dynarray_value(tokens, i);
		if (token->type == OP_PARENTHESIS_OPEN)
			parenthesis.open++;
		else if (token->type == OP_PARENTHESIS_CLOSE)
			parenthesis.close++;
		if (parenthesis.open == parenthesis.close)
			return (count);
		count++;
		i++;
	}
	return (count);
}

static t_ast	*handle_parenthesis_cmd(t_ast_ctx *args, t_ast *cmd_p)
{
	t_ast_ctx	ast_ctx;
	int			count;

	count = count_token_between_brackets(args->tokens, args->i);
	ast_ctx = init_ast_glbctx(args->tokens, args->i, args->i + count, cmd_p);
	add_master_cmds(&ast_ctx);
	if (ast_ctx.has_malloc_error)
		return (NULL);
	args->i += count + 1;
	return (cmd_p);
}

/**
 * 
 * @brief Handles the case where the command is a parenthesis operation.
 * Gets the command inside the parentheses and
 * adds it to the master command node.
 * 
 * @param args The arguments structure containing the tokens and indices.
 * @param cmd_master The master command node to which
 * the new command will be added.
 * 
 * @note If the master command node isn't of type CMD_SUBSHELL,
 * it initializes a CMD_SUBSHELL node.
 * 
*/
void	add_parenthesis_cmd(
	t_ast_ctx *args,
	t_ast *cmd_master,
	t_ast **cmd_prev
)
{
	const t_bool	is_on_stack = cmd_master->type == CMD_SUBSHELL;
	t_ast			*cmd_p;
	t_ast			cmd;

	cmd_p = &cmd;
	reset_ast_node(&cmd, CMD_SEQ);
	if (!is_on_stack)
		cmd_p = ast_init_node(args, CMD_SUBSHELL);
	if (args->has_malloc_error)
		return ;
	if (!handle_parenthesis_cmd(args, cmd_p))
	{
		args->has_malloc_error = TRUE;
		if (!is_on_stack)
			destroy_ast(cmd_p);
		return ;
	}
	if (is_on_stack)
		return (add_ast_childs(cmd_master, cmd_p));
	handle_sub_redir2(args, &cmd_p, cmd_prev, cmd_master);
}

/**
 * 
 * @brief Handles the case where the command is a parenthesis operation
 * and handle the case where the command is part of a pipe.
 * 
 * @param cmd_master The master command node to which
 * the new command will be added.
 * @param args The arguments structure containing the tokens and indices.
 * 
 * @note This parenthesis can't be added directly to cmd_master 
 * if it's part of a pipe; it must be wrapped in a CMD_PIPE node instead.
 * 
*/
void	add_parenthesis_cmd_master(t_ast *cmd_master, t_ast_ctx *args)
{
	t_ast	*cmd;
	t_ast	*cmd_pipe;

	cmd = NULL;
	cmd_pipe = get_adjacent_cmd(args,
			count_token_between_brackets(args->tokens, args->i), FALSE);
	if (!args->has_malloc_error)
		cmd = ast_init_node(args, CMD_SUBSHELL);
	if (!args->has_malloc_error)
		add_parenthesis_cmd(args, cmd, NULL);
	if (args->has_malloc_error)
	{
		destroy_ast(cmd);
		return ((void)destroy_ast(cmd_pipe));
	}
	if (cmd_pipe)
	{
		add_child(cmd_pipe, &cmd, args);
		args->i++;
		add_cmd_pipe(&cmd, cmd_pipe, args);
		return (add_child(cmd_master, &cmd_pipe, args));
	}
	else
		return (handle_sub_redir(args, cmd_master, &cmd));
	add_child(cmd_master, &cmd, args);
}
