#include "ast.h"

/**
 * 
 * @brief Retrieves the next command node from the tokens.
 * 
 * @param args The command arguments structure containing the tokens and indices.
 * 
 * @note If an allocation fails, it sets the "has_malloc_error" boolean to true.
 * 
 * @return 1 if a command node is found, 0 if empty or malloc error.
 * 
*/
int get_cmd(t_get_cmd_master *args)
{
	args->local.cmd = &args->local.lcmd;
	get_cmd_primitive(args, &args->local.cmd);
	if (args->local.cmd)
		return (1);
	args->i++;
	return (0);
}
/**
 * 
 * @brief Checks if the current command node matches the given mask.
 * 
 * @param args The command arguments structure containing the current command node.
 * @param mask The mask to check against the command node type.
 * 
 * @return 1 if the command node matches the mask, 0 otherwise.
 * 
*/
int	is_cmd(t_get_cmd_master *args, size_t mask)
{
	return (is_node(args->local.cmd, mask));
}

