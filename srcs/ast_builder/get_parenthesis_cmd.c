#include "ast.h"

static int	count_token_between_brackets(t_dynamic_array *tokens, int i)
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
		token = (t_token *)get_value(tokens, i);
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

int	get_parenthesis_cmd(t_get_cmd_master args, t_ast_node *cmd_master, int *i)
{
	t_dynamic_array	*sub_cmd;
	t_ast_node		*cmd_parenthesis;
	int				count;

	count = count_token_between_brackets(args.tokens, *i);
	sub_cmd = get_cmd_master((t_get_cmd_master){args.tokens, *i, *i + count, args.has_malloc_error});
	if (cmd_master->type == CMD_PARENTHESIS)
		return (add_childs_and_increment(cmd_master, sub_cmd, i, count));
	cmd_parenthesis = init_node_secure(CMD_PARENTHESIS, NULL, args);
	if (!cmd_parenthesis)
		return (0);
	add_childs_and_increment(cmd_parenthesis, sub_cmd, i, count);
	add_child_secure(cmd_master, &cmd_parenthesis, args);
	return (1);
}

t_ast_node *get_next_cmd_not_space(t_get_cmd_master args, int *i, int count)
{
	t_ast_node	*cmd_not_space;

	cmd_not_space = convert_token_to_cmd_secure(
			(t_token *)get_value(args.tokens, *i + count + 1), args);
	if (cmd_not_space && cmd_not_space->type == CMD_SPACE)
	{
		free(cmd_not_space);
		cmd_not_space = convert_token_to_cmd_secure((t_token *)get_value(args.tokens, *i + count + 2), args);
	}
	return (cmd_not_space);
}

int	get_parenthesis_cmd_master(t_get_cmd_master args,
	t_dynamic_array *array, int *i, int pos)
{
	t_ast_node	*cmd_master;
	t_ast_node	*cmd;
	t_ast_node	*next_operator;
	int			count;

	count = count_token_between_brackets(args.tokens, *i);
	next_operator = get_next_cmd_not_space(args, i, count);
	cmd_master = init_node_secure(CMD_PARENTHESIS, NULL, args);
	if (!cmd_master)
		return (0);
	get_parenthesis_cmd(args, cmd_master, i);
	if (next_operator && next_operator->type == CMD_PIPE)
	{
		add_child_secure(next_operator, &cmd_master, args);
		(*i)++;
		if (get_pipe_cmd(next_operator, args, i, &cmd_master) == 1)
			set_dynarray_value_secure(array, pos, next_operator, args);
	}
	else
	{
		free(next_operator);
		set_dynarray_value_secure(array, pos, cmd_master, args);
	}
}
