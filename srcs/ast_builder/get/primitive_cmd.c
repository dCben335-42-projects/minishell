/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:10:17 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/03 17:56:53 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	add_cmd_join_child(
	t_ast_ctx *args,
	t_get_cmd_primitive *d
)
{
	if (d->cmd_temp)
	{
		if (d->cmd_word)
			add_child(d->cmd_word, &d->cmd_temp, args);
		else
			add_child(d->cmd_redir, &d->cmd_temp, args);
	}
	else
	{
		if (d->cmd_word)
			add_child(d->cmd_new, &d->cmd_word, args);
		if (d->cmd_redir && (d->cmd_redir)->child_count >= 3)
			add_child(d->cmd_new, &d->cmd_redir, args);
	}
}

static t_bool	add_cmd_child_logic_loop(
	t_ast_ctx *args,
	t_get_cmd_primitive *d,
	t_token *token
)
{
	if (is_text_token(*token))
	{
		if (!d->cmd_word && !d->cmd_redir
			&& merr(ast_init_node(args, CMD_WORD), &d->cmd_word))
			return (FALSE);
		if (merr(ast_convert_token_to_cmd(args, token), &d->cmd_temp))
			return (FALSE);
		add_cmd_join_child(args, d);
	}
	else
	{
		add_cmd_join_child(args, d);
		if (token->type != M_SPACE
			&& merr(ast_convert_token_to_cmd(args, token), &d->cmd_redir))
			return (FALSE);
	}
	args->i++;
	return (TRUE);
}

static t_ast_node	*add_cmd_child(t_ast_ctx *args, t_get_cmd_primitive *d)
{
	t_token		*token;

	if (is_empty(args))
		return (NULL);
	if (merr(ast_init_node(args, CMD_BASE), &d->cmd_new))
		return (NULL);
	d->cmd_word = NULL;
	d->cmd_redir = NULL;
	d->cmd_temp = NULL;
	while (args->i < args->end)
	{
		token = get_dynarray_value(args->tokens, args->i);
		if (is_control_extended_token(*token))
			break ;
		if (!add_cmd_child_logic_loop(args, d, token))
			return (NULL);
	}
	add_cmd_join_child(args, d);
	return (d->cmd_new);
}

static void	get_node(t_ast_ctx *args, t_token *token, t_ast_node **cmd)
{
	if (token->type & OP_SEMICOL)
		init_node_on_stack(*cmd, CMD_SEMICOL);
	else if (args->local.ctx == CTX_OP && token->type & (OP_AND | OP_OR))
		return (init_node_on_stack(*cmd, CMD_AND));
	else if (args->local.ctx == CTX_PIPE && token->type & OP_PIPE)
		init_node_on_stack(*cmd, CMD_PIPE);
	else if (token->type & OP_PARENTHESIS_OPEN)
		init_node_on_stack(*cmd, CMD_PARENTHESIS_OPEN);
	else if (args->local.ctx == CTX_PIPE && !(token->type & TEXT))
		return (init_node_on_stack(*cmd, CMD_EOF));
	else
		*cmd = ast_convert_token_to_cmd(args, token);
	args->i++;
}

/**
 * 
 * @brief Retrieves the next command node from the tokens.
 * 
 * @param args The AST global context containing the tokens and indices.
 * @param cmd Pointer to fill with the command node.
 * 
 * @note If an allocation fails, it sets the "has_malloc_error" boolean to true.
 * 
*/

void	get_cmd_primitive(t_ast_ctx *args, t_ast_node **cmd)
{
	t_token				*token;
	t_get_cmd_primitive	d;

	if (args->i >= args->end)
		*cmd = NULL;
	token = get_dynarray_value(args->tokens, args->i);
	if (is_cmd_token(*token))
		*cmd = add_cmd_child(args, &d);
	else
		get_node(args, token, cmd);
}
