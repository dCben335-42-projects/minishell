#include "ast.h"

void	get_parenthesis_cmd_master_wrapper(t_ast_node *cmd,
	t_dynarray *cmd_master, t_ast_node **cmd_prev, t_get_cmd_master *args)
{
	free(cmd);
	set_cmd_in_cmd_master(cmd_master, cmd_prev, args);
	get_parenthesis_cmd_master(args, cmd_master, args->local_node_info.pos);
	args->local_node_info.pos++;
}

static int	count_token_between_brackets(t_dynarray *tokens, t_uint i)
{
	int		count;
	int		count_parenthesis_open;
	int		count_parenthesis_close;
	t_token	*token;

	count = 0;
	count_parenthesis_open = 1;
	count_parenthesis_close = 0;
	while (i < tokens->count - 1)
	{
		token = (t_token *)get_dynarray_value(tokens, i);
		if (token->type == TOKEN_OPEN_BRACKET)
			count_parenthesis_open++;
		else if (token->type == TOKEN_CLOSE_BRACKET)
			count_parenthesis_close++;
		if (count_parenthesis_open == count_parenthesis_close)
			return (count);
		count++;
		i++;
	}
	return (count);
}

int	get_parenthesis_cmd(t_get_cmd_master *args, t_ast_node *cmd_master)
{
	t_get_cmd_master	*cmd_master_params;
	t_dynarray			*sub_cmd;
	t_ast_node			*cmd_parenthesis;
	int					count;

	count = count_token_between_brackets(args->tokens, args->i);
	cmd_master_params = init_t_get_cmd_master(args->tokens,
			args->i, args->i + count - 1, args->has_malloc_error);
	if (!cmd_master_params)
	{
		*(args->has_malloc_error) = TRUE;
		return (0);
	}
	sub_cmd = get_cmd_master(cmd_master_params);
	free(cmd_master_params);
	if (cmd_master->type == CMD_PARENTHESIS)
		return (add_childs_and_increment(cmd_master,
				sub_cmd, &(args->i), count));
	cmd_parenthesis = init_node_secure(CMD_PARENTHESIS, NULL, args);
	if (!cmd_parenthesis)
		return (0);
	add_childs_and_increment(cmd_parenthesis, sub_cmd, &(args->i), count);
	add_child_secure(cmd_master, &cmd_parenthesis, args);
	return (1);
}

t_ast_node	*get_next_cmd_not_space(t_get_cmd_master *args, int count)
{
	t_ast_node	*cmd_not_space;
	t_token		*token;
	t_uint		index;

	index = args->i + count;
	token = (t_token *)get_dynarray_value(args->tokens, index + 1);
	cmd_not_space = convert_token_to_cmd_secure(token, args);
	if (cmd_not_space && cmd_not_space->type == CMD_SPACE)
	{
		free(cmd_not_space);
		token = (t_token *)get_dynarray_value(args->tokens, index + 2);
		cmd_not_space = convert_token_to_cmd_secure(token, args);
	}
	return (cmd_not_space);
}

void	get_parenthesis_cmd_master(t_get_cmd_master *args,
	t_dynarray *array, int pos)
{
	t_ast_node	*cmd_master;
	t_ast_node	*next_operator;
	int			count;

	count = count_token_between_brackets(args->tokens, args->i);
	next_operator = get_next_cmd_not_space(args, count);
	cmd_master = init_node_secure(CMD_PARENTHESIS, NULL, args);
	if (!cmd_master)
		return ;
	get_parenthesis_cmd(args, cmd_master);
	if (next_operator && next_operator->type == CMD_PIPE)
	{
		add_child_secure(next_operator, &cmd_master, args);
		args->i++;
		get_pipe_cmd(next_operator, args, &cmd_master);
		set_dynarray_value_secure(array, pos, next_operator, args);
	}
	else
	{
		free(next_operator);
		set_dynarray_value_secure(array, pos, cmd_master, args);
	}
}
