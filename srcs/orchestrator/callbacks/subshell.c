#include "orchestrator.h"
#include "cmd.h"


/**
 * @brief Executes the subshell command in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute or NULL if there are no more commands.
 */
t_ast_node	*exec_subshell(t_shell *shell, t_ast_node *cmd)
{
	t_ast_node  *skiped_cmd;

	skiped_cmd = skip_cmd(cmd);
	shell->last_pid = fork();
	if (shell->last_pid == -1)
	{
		perror("fork");
		shell->exit_code = EXIT_FAILURE;
		return (NULL);
	}
	else if (shell->last_pid == 0)
	{
		cmd = find_next_cmd(cmd);
		while (cmd || cmd != skiped_cmd)
			cmd = handle_cmd(shell, cmd);
		destroy_self(shell, NULL, shell->exit_code);
	}
	shell->exit_code = wait_childrens(shell->last_pid);
	return (skiped_cmd);
}