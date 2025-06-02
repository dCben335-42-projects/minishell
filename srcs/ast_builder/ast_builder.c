#include "ast.h"
#include <stdlib.h>

/**
 * @brief Builds the AST from the given tokens.
 * This function initializes the master node of the AST and
 * calls the command master function to populate it.
 * 
 * @note The master node is initialized with the type CMD_SEQ.
 * 
 * @return t_ast_node* Pointer to the root of the AST or NULL on malloc error.
 */
t_ast_node	*ast_builder(t_dynarray *tokens)
{
	t_get_cmd_master	cmd_master_params;
	t_ast_node			*master_node;

	master_node = init_node(CMD_SEQ, NULL);
	if (!master_node)
		return (NULL);
	cmd_master_params = init_t_get_cmd_master(tokens, 0, tokens->count - 1, master_node);
	get_cmd_master(&cmd_master_params);
	if (cmd_master_params.local.cmd_master && cmd_master_params.has_malloc_error)
		recursive_destroy_node(cmd_master_params.local.cmd_master);
	return (cmd_master_params.local.cmd_master);
}
