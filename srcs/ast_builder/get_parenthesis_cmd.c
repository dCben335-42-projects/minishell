#include "ast.h"

void	get_parenthesis_cmd_master_wrapper(t_dynarray *cmd_master, t_ast_node **cmd_prev, t_get_cmd_master *args)
{
	set_cmd_in_cmd_master(cmd_master, cmd_prev, args);
	get_parenthesis_cmd_master(args, cmd_master, args->local.pos);
	args->local.pos++;
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
	t_dynarray			*sub_cmd;
	t_ast_node			*cmd_parenthesis;
	int					count;

	count = count_token_between_brackets(args->tokens, args->i);
	cmd_master_params = init_t_get_cmd_master(args->tokens, args->i, args->i + count);
	sub_cmd = get_cmd_master(&cmd_master_params);
	if (cmd_master_params.has_malloc_error)
	{
		args->has_malloc_error = TRUE;
		return ;
	}
	if (cmd_master->type == CMD_PARENTHESIS)
		return ((void)add_childs_and_increment(cmd_master,
				sub_cmd, &(args->i), count));
	cmd_parenthesis = init_node_secure(CMD_PARENTHESIS, NULL, args);
	if (args->has_malloc_error)
		return ;
	add_childs_and_increment(cmd_parenthesis, sub_cmd, &(args->i), count);
	add_child_secure(cmd_master, &cmd_parenthesis, args);
}

t_ast_node	*get_adjacent_cmd(t_get_cmd_master *args, int count)
{
	t_token		*token;

	token = (t_token *)get_dynarray_value(args->tokens, args->i + count + 1);
	if (token && token->type & SPACE)
		token = (t_token *)get_dynarray_value(args->tokens, args->i + count + 2);
	if (token && token->type & OP_PIPE)
		return (init_node_secure(CMD_PIPE, NULL, args));
	return (NULL);
}

void	get_parenthesis_cmd_master(t_get_cmd_master *args,
	t_dynarray *array, int pos)
{
	t_ast_node	*cmd_master;
	t_ast_node	*cmd_pipe;

	cmd_pipe = get_adjacent_cmd(args, count_token_between_brackets(args->tokens, args->i));
	if (args->has_malloc_error)
		return ;
	cmd_master = init_node_secure(CMD_PARENTHESIS, NULL, args);
	if (args->has_malloc_error)
		return ;
	get_parenthesis_cmd(args, cmd_master);
	if (args->has_malloc_error)
		return ;
	if (cmd_pipe)
	{
		add_child_secure(cmd_pipe, &cmd_master, args);
		args->i++;
		get_pipe_cmd(cmd_pipe, args, &cmd_master);
		set_dynarray_value_secure(array, pos, cmd_pipe, args);
	}
	else
		set_dynarray_value_secure(array, pos, cmd_master, args);
}
