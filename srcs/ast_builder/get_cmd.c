#include "ast.h"

static inline void	remove_last_cmd_if_space(t_token *last_token,
	t_bool *is_finished_by_space, t_uint *count)
{
	if (last_token && last_token->type == TOKEN_SPACE)
	{
		*is_finished_by_space = TRUE;
		(*count)--;
	}
}

int	count_new_cmd_child(t_get_cmd_master *args, t_bool *is_finished_by_space)
{
	t_token		*token;
	t_token		*last_token;
	t_uint		count;
	t_uint		start;

	last_token = NULL;
	start = args->i;
	count = 0;
	token = (t_token *)get_dynarray_value(args->tokens, start);
	while (start < args->end && !is_operator_token(*token)
		&& !is_parenthesis_token(*token))
	{
		if (token->type == TOKEN_SPACE && count == 0)
			args->i++;
		else
		{
			last_token = token;
			count++;
		}
		start++;
		if (start < args->end)
			token = (t_token *)get_dynarray_value(args->tokens, start);
	}
	remove_last_cmd_if_space(last_token, is_finished_by_space, &count);
	return (count);
}

t_ast_node	*add_cmd_child(t_get_cmd_master *args,
	t_bool *is_empty, t_token *token)
{
	int			count;
	t_bool		is_finished_by_space;
	t_ast_node	*new_cmd;
	t_ast_node	*temp_cmd;

	is_finished_by_space = FALSE;
	count = count_new_cmd_child(args, &is_finished_by_space);
	if (count > 0)
		new_cmd = init_node_secure(CMD_JOIN, NULL, args);
	else
	{
		*is_empty = TRUE;
		return (NULL);
	}
	while (count--)
	{
		token = (t_token *)get_dynarray_value(args->tokens, args->i);
		temp_cmd = convert_token_to_cmd_secure(token, args);
		add_child_secure(new_cmd, &temp_cmd, args);
		args->i++;
	}
	if (is_finished_by_space)
		args->i++;
	return (new_cmd);
}

void	get_cmd_primitive(t_get_cmd_master *args, t_bool *is_empty, t_ast_node **cmd)
{
	t_token		*token;

	printf("cmd3 = %p\n", *cmd);
	*is_empty = FALSE;
	if (args->i >= args->end)
		*cmd = NULL;
	token = (t_token *)get_dynarray_value(args->tokens, args->i);
	if (is_text_token(*token) || is_redir_token(*token)
		|| token->type == TOKEN_SPACE)
		*cmd = add_cmd_child(args, is_empty, token);
	else
	{
		args->i++;
		if (args->local.ctx == CTX_AND_OR && token->type & (OP_AND | OP_OR))
		{
			args->i--;
			init_node_on_stack(cmd, CMD_AND, NULL);
		}
		if (args->local.ctx == CTX_PIPE && token->type & OP_PIPE)
			init_node_on_stack(cmd, CMD_PIPE, NULL);
		else if (token->type & OP_PARENTHESIS_OPEN)
			init_node_on_stack(cmd, CMD_PARENTHESIS_OPEN, NULL);
		else if (args->local.ctx == CTX_PIPE && !(token->type & TEXT))
		{
			args->i--;
			init_node_on_stack(cmd, CMD_EOF, NULL);
		}
		else
			*cmd = convert_token_to_cmd_secure(token, args);
	}
}
