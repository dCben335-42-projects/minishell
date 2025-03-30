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
	int				sub_cmd_count;
	int				count;

	sub_cmd_count = 0;
	count = count_token_between_brackets(args.tokens, *i);
	sub_cmd = get_cmd_master((t_get_cmd_master){args.tokens, *i, *i + count});
	if (cmd_master->type == CMD_PARENTHESIS)
	{
		while (sub_cmd_count < sub_cmd->count)
		{
			add_child(cmd_master,
				(t_ast_node *)get_value(sub_cmd, sub_cmd_count));
			sub_cmd_count++;
		}
		*i += count + 1;
		return (1);
	}
	cmd_parenthesis = init_node(CMD_PARENTHESIS, NULL);
	while (sub_cmd_count < sub_cmd->count)
	{
		add_child(cmd_parenthesis,
			(t_ast_node *)get_value(sub_cmd, sub_cmd_count));
		sub_cmd_count++;
	}
	add_child(cmd_master, cmd_parenthesis);
	*i += count + 1;
	return (1);
}

int	get_parenthesis_cmd_master(t_get_cmd_master args,
	t_dynamic_array *array, int *i, int pos)
{
	t_ast_node	*cmd_master;
	t_ast_node	*cmd;
	t_ast_node	*prev_cmd;
	int			count;

	count = count_token_between_brackets(args.tokens, *i);
	prev_cmd = convert_token_to_cmd(
			(t_token *)get_value(args.tokens, *i + count + 1));
	cmd_master = init_node(CMD_PARENTHESIS, NULL);
	get_parenthesis_cmd(args, cmd_master, i);
	if (prev_cmd && prev_cmd->type == CMD_PIPE)
	{
		add_child(prev_cmd, cmd_master);
		(*i)++;
		if (get_pipe_cmd(prev_cmd, args, i, &cmd_master) == 1)
			set_value(array, pos, prev_cmd);
	}
	else
		set_value(array, pos, cmd_master);
}
