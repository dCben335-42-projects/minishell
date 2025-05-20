#include "ast.h"

t_ast_node	*convert_token_to_cmd_secure(t_token *token, t_get_cmd_master *args)
{
	t_ast_node	*cmd;

	cmd = convert_token_to_cmd(token);
	if (!cmd)
	{
		args->has_malloc_error = TRUE;
		return (NULL);
	}
	return (cmd);
}

t_ast_node	*init_node_secure(t_node_type type, char *value, t_get_cmd_master *args)
{
	t_ast_node	*node;

	node = init_node(type, value);
	if (!node)
	{
		args->has_malloc_error = TRUE;
		return (NULL);
	}
	return (node);
}

t_get_cmd_master	init_t_get_cmd_master(t_dynarray *tokens,
	int start, int end, t_ast_node *cmd_master)
{
	t_get_cmd_master	args;

	args.tokens = tokens;
	args.start = start;
	args.i = start;
	args.end = end;
	args.local.cmd_master = cmd_master;
	args.has_malloc_error = FALSE;
	return (args);
}

