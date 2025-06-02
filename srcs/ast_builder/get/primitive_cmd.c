/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:10:17 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/02 20:23:06 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_bool	is_empty(t_ast_ctx *args)
{
	t_token	*token;

	token = get_dynarray_value(args->tokens, args->i);
	if (token->type == M_SPACE)
		token = get_dynarray_value(args->tokens, args->i + 1);
	if (token->type == M_EOF)
		return (TRUE);
	if (is_control_extended_token(*token))
		return (TRUE);
	return (FALSE);
}

static void	add_cmd_join_child(t_ast_ctx *args, t_get_cmd_primitive *d, t_ast_node **cmd_word, t_ast_node **cmd_redir)
{
	if (*cmd_word)
		add_child(d->cmd_new, cmd_word, args);
	if (*cmd_redir && (*cmd_redir)->child_count >= 3)
		add_child(d->cmd_new, cmd_redir, args);
}

t_bool	merr(t_ast_node *node, t_ast_node **out)
{
	if (!node)
		return (TRUE);
	*out = node;
	return (FALSE);
}

static t_ast_node	*add_cmd_child(t_ast_ctx *args, t_get_cmd_primitive *d)
{
	t_token		*token;
	t_ast_node	*cmd_word;
	t_ast_node	*cmd_redir;

	if (is_empty(args))
		return (NULL);
	if (merr(ast_init_node(args, CMD_BASE), &d->cmd_new))
		return (NULL);
	cmd_word = NULL;
	cmd_redir = NULL;
	while (args->i < args->end)
	{
		token = get_dynarray_value(args->tokens, args->i);
		if (is_control_extended_token(*token))
			break;
		if (is_text_token(*token))
		{
			if (!cmd_word && !cmd_redir && merr(ast_init_node(args, CMD_WORD), &cmd_word))
				return (NULL);
			if (merr(ast_convert_token_to_cmd(args, token), &d->cmd_temp))
				return (NULL);
			if (cmd_word)
				add_child(cmd_word, &d->cmd_temp, args);
			else
				add_child(cmd_redir, &d->cmd_temp, args);
		}
		else if (token->type == M_SPACE)
			add_cmd_join_child(args, d, &cmd_word, &cmd_redir);
		else
		{
			add_cmd_join_child(args, d, &cmd_word, &cmd_redir);
			if (merr(ast_convert_token_to_cmd(args, token), &cmd_redir))
				return (NULL);
		}
		args->i++;
	}
	add_cmd_join_child(args, d, &cmd_word, &cmd_redir);
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
