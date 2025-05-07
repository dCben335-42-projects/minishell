#include "ast.h"

//static inline void	remove_last_cmd_if_space(t_token *last_token, t_count_cmd_child *counter)
//{
//	if (last_token && last_token->type == TOKEN_SPACE)
//	{
//		counter->space_at_end = TRUE;
//		counter->count--;
//	}
//}

//static void	count_new_cmd_child(t_get_cmd_master *args, t_count_cmd_child *counter)
//{
//	t_token		*token;
//	//t_token		*next_token;
//	t_token		*last_token;
//	t_uint		start;

//	last_token = NULL;
//	start = args->i;
//	counter->count = 0;
//	token = (t_token *)get_dynarray_value(args->tokens, start);
//	while (start < args->end && !is_operator_ext_token(*token))
//	{
//		if (token->type == TOKEN_SPACE && !counter->count)
//			args->i++;
//		else
//		{
//			last_token = token;
//			counter->count++;
//		}
//		start++;
//		if (start < args->end)
//			token = (t_token *)get_dynarray_value(args->tokens, start);
//	}
//	remove_last_cmd_if_space(last_token, counter);
//}

//t_bool	keep_only_space_between_text(t_get_cmd_master *args)
//{
//	t_token	*prev_token;
//	t_token	*token;
//	t_token *next_token;

//	token = (t_token *)get_dynarray_value(args->tokens, args->i);
//	if (token->type == TOKEN_SPACE)
//	{
//		if (args->i > 0)
//			prev_token = (t_token *)get_dynarray_value(args->tokens, args->i - 1);
//		next_token = (t_token *)get_dynarray_value(args->tokens, args->i + 1);
//		if (prev_token && !is_text_token(*prev_token))
//			return (FALSE);
//		if (next_token && !is_text_token(*next_token))
//			return (FALSE);
//	}
//	return (TRUE);
//}

static t_ast_node	*add_cmd_child(t_get_cmd_master *args, t_get_cmd_primitive *d)
{
	t_token		*token;
	t_ast_node	*cmd_word;
	t_ast_node	*cmd_redir;

	cmd_word = NULL;
	cmd_redir = NULL;
	d->cmd_new = init_node_secure(CMD_JOIN, NULL, args);
	if (args->has_malloc_error)
		return (NULL);
	token = (t_token *)get_dynarray_value(args->tokens, args->i);

	while (args->i < args->end && !is_operator_ext_token(*token))
	{
		if (is_text_token(*token))
		{
			if (!cmd_word && !cmd_redir)
				cmd_word = init_node_secure(CMD_WORD, NULL, args);
			d->cmd_temp = convert_token_to_cmd_secure(token, args);
			if (args->has_malloc_error)
				return (NULL);
			if (cmd_word)
				add_child(cmd_word, &d->cmd_temp, args);
			else if (cmd_redir)
				add_child(cmd_redir, &d->cmd_temp, args);
		}
		else if (token->type == TOKEN_SPACE)
		{
			if (cmd_word)
				add_child(d->cmd_new, &cmd_word, args);
			if (cmd_redir && cmd_redir->child_count >= 3)
				add_child(d->cmd_new, &cmd_redir, args);
			args->i++;
			if (args->i < args->end)
				token = (t_token *)get_dynarray_value(args->tokens, args->i);
			continue;
		}
		else
		{
			if (cmd_word)
				add_child(d->cmd_new, &cmd_word, args);
			if (cmd_redir)
				add_child(d->cmd_new, &cmd_redir, args);
			if (is_redir_token(*token))
			{
				cmd_redir = convert_token_to_cmd_secure(token, args);
				if (args->has_malloc_error)
					return (NULL);
				args->i++;
				if (args->i < args->end)
					token = (t_token *)get_dynarray_value(args->tokens, args->i);
				continue;
			}
			d->cmd_temp = convert_token_to_cmd_secure(token, args);
			if (args->has_malloc_error)
				return (NULL);
			add_child(d->cmd_new, &d->cmd_temp, args);
		}
		args->i++;
		if (args->i < args->end)
			token = (t_token *)get_dynarray_value(args->tokens, args->i);
	}
	if (cmd_word)
		add_child(d->cmd_new, &cmd_word, args);
	if (cmd_redir)
		add_child(d->cmd_new, &cmd_redir, args);
	if (!d->cmd_new->child_count)
	{
		*d->is_empty = TRUE;
		free(d->cmd_new);
	}
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

void	get_cmd_primitive(t_get_cmd_master *args, t_bool *is_empty, t_ast_node **cmd)
{
	t_token				*token;
	t_get_cmd_primitive	d;

	*is_empty = FALSE;
	d.is_empty = is_empty;
	if (args->i >= args->end)
		*cmd = NULL;
	token = (t_token *)get_dynarray_value(args->tokens, args->i);
	if (is_cmd_token(*token))
		*cmd = add_cmd_child(args, &d);
	else
		get_node(args, token, cmd);
}
