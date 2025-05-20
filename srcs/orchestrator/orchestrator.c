#include "ast.h"
#include "orchestrator.h"
#include "cmd.h"
#include "cmd_expand.h"
#include "cmd_builtin.h"
#include <fcntl.h>
#include <unistd.h>
# include "cmd.h"
#include <fcntl.h>
#include <unistd.h>

static const t_exec_map	*get_exec_map(void)
{
	static const t_exec_map	map[] = {
	{CMD_SEQ, &exec_basic},
	{CMD_JOIN, &exec_basic},
	{CMD_AND, &exec_and},
	{CMD_OR, &exec_or},
	{CMD_PIPE, &exec_pipeline},
	{CMD_PARENTHESIS, &exec_subshell},
	{0, NULL}};

	return (map);
}


t_bool  is_only_redir(t_ast_node *cmd)
{
	t_uint	i;
	t_ast_node	*node;
	t_dynarray	*arr;

	if (cmd->type != CMD_JOIN)
		return (FALSE);
	i = 0;
	arr = cmd->content;
	while (i < arr->count)
	{
		node = get_dynarray_value(cmd->content, i);
		if (!is_redirection(node->type))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * @brief Checks if the given node type is a valid execution type.
 * 
 * @param type The node type to check.
 * 
 * @return TRUE if the type is valid, FALSE otherwise.
 */
t_bool is_valid_exec_type(const t_node_type type)
{
	const t_exec_map	*map = get_exec_map();

	while (map->type)
	{
		if (map->type == type)
			return (TRUE);
		map++;
	}
	return (FALSE);
}


/**
 * @brief Handles the execution of a command in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute or NULL if there are no more commands.
 */
t_ast_node	*handle_cmd(t_shell *shell, t_ast_node *cmd)
{
	const t_exec_map	*exec_map = get_exec_map();

	while (exec_map->type)
	{
		if (exec_map->type == cmd->type)
			return (exec_map->f(shell, cmd));
		exec_map++;
	}
	return (NULL);
}


/**
 * @brief Orchestrator function that handles the execution of commands in the shell.
 * It finds the next command to execute and calls the appropriate handler function.
 * 	
 * @param shell The shell structure containing the current state.
 * 
 * @return void
 * 
 * @note This function is responsible for managing the execution flow of commands in the shell.
 * It iterates through the AST (Abstract Syntax Tree) of commands, executing each command
 * in the appropriate context (e.g., subshell, pipe, etc.). The function continues to find
 * and execute commands until there are no more commands to process.
 * 
*/
void	orchestrator(t_shell *shell)
{
	t_ast_node	*cmd;

	cmd = find_next_cmd(shell->ast);
	while (cmd)
		cmd = handle_cmd(shell, cmd);
}
