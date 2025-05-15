#include "orchestrator.h"

/**
 * @brief Executes the PIPE command in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute or NULL if there are no more commands.
 */
t_ast_node	*exec_pipe(t_shell *shell, t_ast_node *cmd)
{
	(void)cmd;
	(void)shell;
	return (skip_cmd(cmd));
}