#include "ast.h"

t_ast_node	*convert_token_to_cmd_secure(t_token *token, t_get_cmd_master *args)
{
	t_ast_node	*cmd;

	cmd = convert_token_to_cmd(token);
	if (!cmd)
	{
		printf("convert_token_to_cmd_secure\n");
		*(args->has_malloc_error) = TRUE;
		return (NULL);
	}
	return (cmd);
}

void	*init_node_secure(t_node_type type, char *value, t_get_cmd_master *args)
{
	t_ast_node	*node;

	node = init_node(type, value);
	if (!node)
	{
		printf("init_node_secure\n");
		*(args->has_malloc_error) = TRUE;
		return (NULL);
	}
	return (node);
}

t_get_cmd_master	*init_t_get_cmd_master(t_dynamic_array *tokens,
	int start, int end, t_bool *has_malloc_error)
{
	t_get_cmd_master	*args;

	args = malloc(sizeof(t_get_cmd_master));
	if (!args)
		return (NULL);
	args->tokens = tokens;
	args->start = start;
	args->i = start;
	args->end = end;
	args->has_malloc_error = has_malloc_error;
	return (args);
}

t_bool	is_true_then_false(t_bool *val)
{
	if (*val)
	{
		*val = FALSE;
		return (TRUE);
	}
	return (FALSE);
}
