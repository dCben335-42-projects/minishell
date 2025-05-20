#include "ast.h"

t_bool	is_empty(t_get_cmd_master *args)
{
	t_token	*token;

	token = (t_token *)get_dynarray_value(args->tokens, args->i);
	if (token->type == M_SPACE)
		token = (t_token *)get_dynarray_value(args->tokens, args->i + 1);
	if (token->type == M_EOF)
		return (TRUE);
	if (is_control_extended_token(*token))
		return (TRUE);
	return (FALSE);
}

static void	add_cmd_join_child(t_get_cmd_master *args, t_get_cmd_primitive *d, t_ast_node **cmd_word, t_ast_node **cmd_redir)
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

static t_ast_node	*add_cmd_child(t_get_cmd_master *args, t_get_cmd_primitive *d)
{
	t_token		*token;
	t_ast_node	*cmd_word;
	t_ast_node	*cmd_redir;

	if (is_empty(args))
		return (NULL);
	if (merr(init_node_secure(CMD_JOIN, NULL, args), &d->cmd_new))
		return (NULL);
	cmd_word = NULL;
	cmd_redir = NULL;
	while (args->i < args->end)
	{
		token = (t_token *)get_dynarray_value(args->tokens, args->i);
		if (is_control_extended_token(*token))
			break;
		if (is_text_token(*token))
		{
			if (!cmd_word && !cmd_redir && merr(init_node_secure(CMD_WORD, NULL, args), &cmd_word))
				return (NULL);
			if (merr(convert_token_to_cmd_secure(token, args), &d->cmd_temp))
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
			if (merr(convert_token_to_cmd_secure(token, args), &cmd_redir))
				return (NULL);
		}
		args->i++;
	}
	add_cmd_join_child(args, d, &cmd_word, &cmd_redir);
	return (d->cmd_new);
}

// bonjour$PATH sa va <<?.txt$DUZHDU
static void	get_node(t_get_cmd_master *args, t_token *token, t_ast_node **cmd)
{
	if (token->type & OP_SEMICOL)
		init_node_on_stack(*cmd, CMD_SEMICOL);
	else if (args->local.ctx == CTX_AND_OR && token->type & (OP_AND | OP_OR))
		return (init_node_on_stack(*cmd, CMD_AND));
	else if (args->local.ctx == CTX_PIPE && token->type & OP_PIPE)
		init_node_on_stack(*cmd, CMD_PIPE);
	else if (token->type & OP_PARENTHESIS_OPEN)
		init_node_on_stack(*cmd, CMD_PARENTHESIS_OPEN);
	else if (args->local.ctx == CTX_PIPE && !(token->type & TEXT))
		return (init_node_on_stack(*cmd, CMD_EOF));
	else
		*cmd = convert_token_to_cmd_secure(token, args);
	args->i++;
}

void	get_cmd_primitive(t_get_cmd_master *args, t_ast_node **cmd)
{
	t_token				*token;
	t_get_cmd_primitive	d;

	if (args->i >= args->end)
		*cmd = NULL;
	token = (t_token *)get_dynarray_value(args->tokens, args->i);
	if (is_cmd_token(*token))
		*cmd = add_cmd_child(args, &d);
	else
		get_node(args, token, cmd);
}
