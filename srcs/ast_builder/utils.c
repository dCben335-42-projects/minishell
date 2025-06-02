#include "ast.h"

/**
 * @brief Converts a token to a command node.
 * 
 * @note If an allocation fails, it sets the "has_malloc_error" boolean to true.
 * 
 * @return t_ast_node* Pointer to the command node or NULL on malloc error.
 */
t_ast_node	*convert_token_to_cmd_secure(t_token *token, t_get_cmd_master *args)
{
	t_ast_node	*node;

	node = convert_token_to_cmd(token);
	if (!node)
	{
		args->has_malloc_error = TRUE;
		return (NULL);
	}
	return (node);
}

/**
 * 
 * @brief Initializes a new AST node with the given type and value.
 * 
 * @note If an allocation fails, it sets the "has_malloc_error" boolean to true.
 * 
 * @return t_ast_node* Pointer to the initialized node or NULL on malloc error.
 * 
*/
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

/**
 * 
 * @brief Initializes the t_get_cmd_master structure with the given parameters.
 * 
 * @param tokens The dynamic array of tokens.
 * @param start The starting index in the tokens array.
 * @param end The ending index in the tokens array.
 * @param cmd_master The command master node to be initialized.
 * 
 * @return t_get_cmd_master initialized structure with the provided parameters.
 * 
*/
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

