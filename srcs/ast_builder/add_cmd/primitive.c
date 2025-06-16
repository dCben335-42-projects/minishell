/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:10:17 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/16 18:03:40 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_builder.h"

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
		return ;
	}
	if (d->cmd_word)
		add_child(d->cmd_new, &d->cmd_word, args);
	if (d->cmd_redir && (d->cmd_redir)->child_count >= 3)
		add_child(d->cmd_new, &d->cmd_redir, args);
}

static t_bool	add_cmd_child_logic_loop(
	t_ast_ctx *args,
	t_get_cmd_primitive *d,
	t_token *token
)
{
	if (is_text_token(token))
	{
		if ((!d->cmd_word && !d->cmd_redir
				&& ast_merr(ast_init_node(args, CMD_WORD), &d->cmd_word)))
			return (FALSE);
		if (ast_merr(ast_convert_token_to_cmd(args, token), &d->cmd_temp))
			return (FALSE);
		add_cmd_join_child(args, d);
	}
	else
	{
		add_cmd_join_child(args, d);
		if (token->type != M_SPACE
			&& ast_merr(ast_convert_token_to_cmd(args, token), &d->cmd_redir))
			return (FALSE);
	}
	args->i++;
	return (TRUE);
}

static t_ast	*add_cmd_child(t_ast_ctx *args)
{
	t_get_cmd_primitive	d;
	t_token				*token;

	if (is_empty(args))
		return (NULL);
	if (ast_merr(ast_init_node(args, CMD_BASE), &d.cmd_new))
		return (NULL);
	d.cmd_word = NULL;
	d.cmd_redir = NULL;
	d.cmd_temp = NULL;
	while (args->i < args->end)
	{
		token = get_dynarray_value(args->tokens, args->i);
		if (is_control_extended_token(token))
			break ;
		if (!add_cmd_child_logic_loop(args, &d, token))
			break ;
	}
	add_cmd_join_child(args, &d);
	destroy_ast(d.cmd_temp);
	destroy_ast(d.cmd_word);
	destroy_ast(d.cmd_redir);
	return (d.cmd_new);
}

/**
 * 
 * @brief Initializes the command node based on the current token.
 * 
 * @param args The AST global context containing the tokens and indices.
 * @param token The current token to process.
 * @param cmd Pointer to fill with the command node.
 * 
 * 
 * @note 
 * 	In a pipe context :
 * 
 * - if a pipe token is found, it initializes on the stack
 * a CMD_PIPE node to indicate that an other command is in the pipe.
 * 
 * - if a semicolon token is found, it initializes on the stack
 * a CMD_SEMICOL node to indicate that the command is finished.

 * - if a parenthesis open token is found, it initializes* on the stack
 	a CMD_PARENTHESIS_OPEN node to indicate that a subshell is starting
 *	inside the pipe.
 * 
 * - else, it initializes a EOF node to indicate that the command is finished
 * 
 * In an operator context :
 * 
 * - if an AND or OR token is found, it initializes on the stack
 * a CMD_AND node to indicate that the current command is finished
 * 
 * - if a semicolon token is found, it initializes on the stack
 * a CMD_SEMICOL node to indicate that the command is finished.
 * 
 * - if a parenthesis open token is found, it initializes on the stack
 * a CMD_PARENTHESIS_OPEN node to indicate that a subshell is starting
 * inside the operator.	
 * 
 * In a master context :
 * - if an control token (OP_AND, OP_OR, ) is found, it initializes on the heap
 * 	a note according to the token type that will be added to the AST.
 * 
 * 
 * @note Node that are on the stack are meant to be used as a temporary node
 * and won't be added to the AST.
 * 
 * @note When we don't increment the index (args->i) after initializing 
 * a node on the stack,
 * it means that the node will be processed in the next iteration
 * 
 * @note If the token is a control token (like OP_SEMICOL, OP_AND, OP_OR, etc.),
 * 
*/
static void	get_node(t_ast_ctx *args, t_token *token, t_ast **cmd)
{
	if (token->type & OP_SEMICOL)
		reset_ast_node(*cmd, CMD_SEMICOL);
	else if (args->local.ctx == CTX_OP && token->type & (OP_AND | OP_OR))
		return (reset_ast_node(*cmd, CMD_AND));
	else if (args->local.ctx == CTX_PIPE && token->type & OP_PIPE)
		reset_ast_node(*cmd, CMD_PIPE);
	else if (token->type & OP_PARENTHESIS_OPEN)
		reset_ast_node(*cmd, CMD_PARENTHESIS_OPEN);
	else if (args->local.ctx == CTX_PIPE)
		return (reset_ast_node(*cmd, CMD_EOF));
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
 * @note 
 * If the current token (got from args->i) is text token, It will:
 * 
 * - create a whole command node (CMD_BASE) and fill it with
 * the command children.
 * 
 * - regroup every text token into a CMD_WORD node,
 * and every redirection token into a CMD_REDIR node.
 * 
 * Otherwise, it will either create a indicator node in the stack
 * or convert the token to a command node on the heap
 * 
 * @note If an allocation fails, it sets the "has_malloc_error" boolean to true.
 * 
*/
void	add_cmd_primitive(t_ast_ctx *args, t_ast **cmd)
{
	t_token				*token;

	if (args->i >= args->end)
		*cmd = NULL;
	token = get_dynarray_value(args->tokens, args->i);
	if (is_cmd_token(token))
		*cmd = add_cmd_child(args);
	else
		get_node(args, token, cmd);
}
