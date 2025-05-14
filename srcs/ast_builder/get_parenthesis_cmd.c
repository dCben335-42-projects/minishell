#include "ast.h"

static int	count_token_between_brackets(t_dynarray *tokens, t_uint i)
{
	int			count;
	t_bracket	parenthesis;
	t_token		*token;

	count = 0;
	parenthesis = (t_bracket){1, 0};
	while (i < tokens->count - 1)
	{
		token = (t_token *)get_dynarray_value(tokens, i);
		if (token->type == TOKEN_PARENTHESIS_OPEN)
			parenthesis.open++;
		else if (token->type == TOKEN_PARENTHESIS_CLOSE)
			parenthesis.close++;
		if (parenthesis.open == parenthesis.close)
			return (count);
		count++;
		i++;
	}
	return (count);
}

void	get_parenthesis_cmd(t_get_cmd_master *args, t_ast_node *cmd_master)
{
	t_get_cmd_master	cmd_master_params;
	t_ast_node			cmd;
	t_ast_node			*cmd_p;
	int					count;

	cmd_p = &cmd;
	if (cmd_master->type == CMD_PARENTHESIS)
		init_node_on_stack(&cmd, CMD_SEQ);
	else
		cmd_p = init_node_secure(CMD_PARENTHESIS, NULL, args);
	if (args->has_malloc_error)
		return ;
	count = count_token_between_brackets(args->tokens, args->i);
	cmd_master_params = init_t_get_cmd_master(args->tokens, args->i, args->i + count, cmd_p);
	get_cmd_master(&cmd_master_params);
	if (cmd_master_params.has_malloc_error)
	{
		args->has_malloc_error = TRUE;
		return ;
	}
	args->i += count + 1;
	if (cmd_master->type == CMD_PARENTHESIS)
		return (add_childs(cmd_master, cmd_p->content));
	add_child(cmd_master, &cmd_p, args);
}

static t_ast_node	*get_adjacent_cmd(t_get_cmd_master *args, int count)
{
	t_token		*token;

	token = (t_token *)get_dynarray_value(args->tokens, args->i + count + 1);
	if (token && token->type & M_SPACE)
		token = (t_token *)get_dynarray_value(args->tokens, args->i + count + 2);
	if (token && token->type & OP_PIPE)
		return (init_node_secure(CMD_PIPE, NULL, args));
	return (NULL);
}

void	get_parenthesis_cmd_master(t_ast_node *cmd_master, t_get_cmd_master *args)
{
	t_ast_node	*cmd;
	t_ast_node	*cmd_pipe;

	cmd_pipe = get_adjacent_cmd(args, count_token_between_brackets(args->tokens, args->i));
	if (args->has_malloc_error)
		return ;
	cmd = init_node_secure(CMD_PARENTHESIS, NULL, args);
	if (args->has_malloc_error)
		return ;
	get_parenthesis_cmd(args, cmd);
	if (args->has_malloc_error)
		return ;
	if (cmd_pipe)
	{
		add_child(cmd_pipe, &cmd, args);
		args->i++;
		get_pipe_cmd(&cmd, cmd_pipe, args);
		return (add_child(cmd_master, &cmd_pipe, args));
	}
	add_child(cmd_master, &cmd, args);
}
