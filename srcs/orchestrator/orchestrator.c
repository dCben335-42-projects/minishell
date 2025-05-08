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



void	cleanup_args(t_dynarray *arr)
{
	t_uint	i;
	t_uint	j;
	t_uint	count;
	char	*str;
	
	count = arr->count;
	i = 0;
	j = 0;
	if (!arr || !arr->data)
		return;
	while (i < count)
	{
		str = (char *)arr->data[i];
		if (str && *str)
			arr->data[j++] = arr->data[i];
		else if (arr->destroyer)
			arr->destroyer(arr->data[i]); 
		i++;
	}
	arr->count = j;
	while (j < count)
		arr->data[j++] = NULL;
}
t_bool	is_cmd_redirection(t_dynarray *cmd);
t_bool	handle_redirections(t_shell *shell, t_dynarray *cmd);
void restore_std_in_out(int saved_stdin, int saved_stdout);
void f_savestd(
	t_shell *shell,
	t_dynarray *cmd,
	char **args,
	void (*f)(t_shell *, char **)
);

#include "errors.h"

void exec2(t_shell *shell, t_dynarray *args, t_dynarray *cmd)
{
	char		**argv;

	argv = (char **)args->data;
	if (!is_builtin(shell, cmd, argv, FALSE))
	{
		argv[0] = get_full_cmd_path(argv, get_env_node(shell->env, "PATH"));
		fork_and_exec(shell, args, argv, cmd);
	}
}

void exec(t_shell *shell, t_dynarray *args, t_dynarray *cmd, t_bool is_subshell)
{
	if (!is_subshell)
		exec2(shell, args, cmd);
}
void	execute_cmd_base(t_shell *shell, t_dynarray *cmd, t_bool is_subshell)
{
	t_dynarray	args;

	args = init_dynarray(1, free_value);
	if (!cmd_to_argv(cmd, &args) || !expand(shell, &args))
		return ;
	cleanup_args(&args);
	exec(shell, &args, cmd, is_subshell);
	destroy_dynarray(&args);
}

void	execute_cmd_and(t_shell *shell, t_dynarray *cmd, t_bool is_subshell)
{
	if (!shell->exit_code)
		execute_cmd_base(shell, cmd, is_subshell);
}
void	execute_cmd_or(t_shell *shell, t_dynarray *cmd, t_bool is_subshell)
{
	if (shell->exit_code)
		execute_cmd_base(shell, cmd, is_subshell);
}

void	execute_cmd_pipe()
{
	return ;
}

void	orchestrator(t_shell *shell)
{
	t_ast_node	*cmd;
	t_ast_node	*master_node;

	master_node = shell->ast;
	cmd = find_next_cmd(master_node);
	while (cmd)
	{
		// print_ast_json_wrapper(cmd->content);
		if (cmd->parent->type == CMD_SEQ)
			execute_cmd_base(shell, cmd->content, FALSE);
		if (cmd->parent->type == CMD_AND)
			execute_cmd_and(shell, cmd->content, FALSE);
		if (cmd->parent->type == CMD_OR)
			execute_cmd_or(shell, cmd->content, FALSE);
		cmd = find_next_cmd(master_node);
	}
}

// ( ( ( echo 'salut' ) ) && echo 'bonjour' ) | echo bar | echo "sa va"