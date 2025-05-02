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

// CMD_PARENTHESIS ne peut imbriqué directement le tout?

void	get_parenthesis_cmd(t_get_cmd_master *args, t_ast_node *cmd_master)
{
	t_get_cmd_master	cmd_master_params;
	t_ast_node			*cmd_parenthesis;
	t_ast_node			master_node;
	int					count;

	count = count_token_between_brackets(args->tokens, args->i);
	init_node_on_stack(&master_node, CMD_SEQ);
	cmd_master_params = init_t_get_cmd_master(args->tokens, args->i, args->i + count, &master_node);
	get_cmd_master(&cmd_master_params);
	if (cmd_master_params.has_malloc_error)
	{
		args->has_malloc_error = TRUE;
		return ;
	}
	if (cmd_master->type == CMD_PARENTHESIS)
		return (add_childs_and_increment(cmd_master, master_node.content, &(args->i), count));
	cmd_parenthesis = init_node_secure(CMD_PARENTHESIS, NULL, args);
	if (args->has_malloc_error)
		return ;
	add_childs_and_increment(cmd_parenthesis, master_node.content, &(args->i), count);
	add_child_secure(cmd_master, &cmd_parenthesis, args);
}

static t_ast_node	*get_adjacent_cmd(t_get_cmd_master *args, int count)
{
	t_token		*token;

	token = (t_token *)get_dynarray_value(args->tokens, args->i + count + 1);
	if (token && token->type & SPACE)
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
		add_child_secure(cmd_pipe, &cmd, args);
		args->i++;
		get_pipe_cmd(&cmd, cmd_pipe, args);
		add_child_secure(cmd_master, &cmd_pipe, args);
	}
	else
		add_child_secure(cmd_master, &cmd, args);
}
