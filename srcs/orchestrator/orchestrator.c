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
	
	if (!arr || !arr->data)
		return;
	count = arr->count;
	i = 0;
	j = 0;
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

void exec2(t_shell *shell, t_dynarray *cmd, char **argv)
{
	if (!is_builtin(shell, cmd, argv, FALSE))
	{
		argv[0] = get_full_cmd_path(argv, get_env_node(shell->env, "PATH"));
		fork_and_exec(shell, argv, cmd);
	}
}

void exec3(t_shell *shell, t_dynarray *cmd, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		shell->exit_code = EXIT_FAILURE;
		return ;
	}
	else if (pid == 0)
	{
		if (!handle_redirections(shell, cmd))
			destroy_child(shell, argv, EXIT_FAILURE);
		if (!is_builtin(shell, cmd, argv, TRUE))
		{
			argv[0] = get_full_cmd_path(argv, get_env_node(shell->env, "PATH"));
			exec_cmd(argv, shell);
		}
		destroy_child(shell, argv, shell->exit_code);
	}
	shell->exit_code = wait_childrens();
}

void exec(t_shell *shell, t_dynarray *cmd, char **argv, t_bool is_subshell)
{
	if (!is_subshell)
		exec2(shell, cmd, argv);
	else
		exec3(shell, cmd, argv);
}		
	
void	execute_cmd_base(t_shell *shell, t_dynarray *cmd, t_bool is_subshell)
{
	t_dynarray	args;

	args = init_dynarray(1, free_value);
	if (!cmd_to_argv(cmd, &args) || !expand(shell, &args))
		return ;
	cleanup_args(&args);
	exec(shell, cmd, (char **)args.data, is_subshell);
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

typedef struct s_exec_map
{
	t_node_type	type;
	void		(*f)(t_shell *shell, t_dynarray *cmd, t_bool is_subshell);
}	t_exec_map;

const t_exec_map	*get_exec_map(void)
{
	static const t_exec_map	map[] = {
	{CMD_SEQ, &execute_cmd_base},
	{CMD_JOIN, &execute_cmd_base},
	{CMD_AND, &execute_cmd_and},
	{CMD_OR, &execute_cmd_or},
	{CMD_PIPE, &execute_cmd_pipe},
	{0, NULL}};

	return (map);
}

void handle_cmd(
	t_shell *shell, 
	t_ast_node *cmd, 
	const t_node_type type,
	t_bool is_subshell
)
{
	const t_exec_map	*exec_map = get_exec_map();

	printf("is subshell: %d\n", is_subshell);
	while (exec_map->type)
	{
		if (exec_map->type == type)
		{
			exec_map->f(shell, cmd->content, is_subshell);
			break ;
		}
		exec_map++;
	}
}

void handle_subshell(
	t_shell *shell, 
	t_ast_node *cmd, 
	const t_node_type type
)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		shell->exit_code = EXIT_FAILURE;
		return ;
	}
	else if (pid == 0)
	{
		if (!handle_redirections(shell, cmd))
			destroy_child(shell, cmd->content, EXIT_FAILURE);
		handle_cmd(shell, cmd, type, TRUE);
		destroy_child(shell, cmd->content, shell->exit_code);
	}
}


void	orchestrator(t_shell *shell)
{
	t_ast_node	*cmd;
	t_ast_node	*master_node;

	master_node = shell->ast;
	cmd = find_next_cmd(master_node);
	printf("=================================================\n");
	while (cmd)
	{
		if (cmd->parent->type == CMD_PARENTHESIS)
			handle_cmd(shell, cmd, cmd->type, TRUE);
		else 
			handle_cmd(shell, cmd, cmd->parent->type, FALSE);
		cmd = find_next_cmd(master_node);
	}
	printf("=================================================\n");
}

// ( ( ( echo 'salut' ) ) && echo 'bonjour' ) | echo bar | echo "sa va"