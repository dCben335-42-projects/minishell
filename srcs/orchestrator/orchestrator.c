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

t_ast_node	*handle_cmd(t_shell *shell, t_ast_node *cmd);

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

#include "errors.h"

void exec2(t_shell *shell, t_dynarray *cmd, char **argv)
{
	if (!is_builtin(shell, cmd, argv))
	{
		argv[0] = get_full_cmd_path(argv, get_env_node(shell->env, "PATH"));
		if (!argv[0])
			destroy_child(shell, argv, EXIT_FAILURE);
		fork_and_exec(shell, argv, cmd);
	}
}


void exec(t_shell *shell, t_dynarray *cmd, char **argv)
{
	exec2(shell, cmd, argv);
}		
	
t_ast_node	*execute_cmd_base(t_shell *shell, t_ast_node *cmd)
{
	t_dynarray	args;

	args = init_dynarray(1, free_value);
	if (!cmd_to_argv(cmd->content, &args))
		return (NULL);
	cleanup_args(&args);
	t_uint	i = 0;
	while (i < args.count)
	{
		printf("args[%d] = %s\n", i, (char *)args.data[i]);
		i++;
	}
	
	exec(shell, cmd->content, (char **)args.data);
	destroy_dynarray(&args);
	return (find_next_cmd(cmd));
}


t_ast_node	*execute_cmd_and(t_shell *shell, t_ast_node *cmd)
{
	if (!shell->exit_code)
		return (handle_cmd(shell, find_next_cmd(cmd)));
	return (skip_cmd(cmd));
}
t_ast_node	*execute_cmd_or(t_shell *shell, t_ast_node *cmd)
{
	if (shell->exit_code)
		return (handle_cmd(shell, find_next_cmd(cmd)));
	return (skip_cmd(cmd));
}

t_ast_node	*execute_cmd_pipe(t_shell *shell, t_ast_node *cmd)
{
	(void)cmd;
	(void)shell;
	return (skip_cmd(cmd));
}



t_ast_node	*handle_subshell(t_shell *shell, t_ast_node *cmd)
{
	t_ast_node  *skiped_cmd;
	pid_t		pid;

	skiped_cmd = skip_cmd(cmd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		shell->exit_code = EXIT_FAILURE;
		return (NULL);
	}
	else if (pid == 0)
	{
		while (cmd != skiped_cmd)
			cmd = handle_cmd(shell, find_next_cmd(cmd));
		destroy_child(shell, NULL, shell->exit_code);
	}
	shell->exit_code = wait_childrens();
	return (skiped_cmd);
}



typedef struct s_exec_map
{
	t_node_type	type;
	t_ast_node	*(*f)(t_shell *shell, t_ast_node *cmd);
}	t_exec_map;

const t_exec_map	*get_exec_map(void)
{
	static const t_exec_map	map[] = {
	{CMD_SEQ, &execute_cmd_base},
	{CMD_JOIN, &execute_cmd_base},
	{CMD_AND, &execute_cmd_and},
	{CMD_OR, &execute_cmd_or},
	{CMD_PIPE, &execute_cmd_pipe},
	{CMD_PARENTHESIS, &handle_subshell},
	{0, NULL}};

	return (map);
}

t_ast_node	*handle_cmd(t_shell *shell, t_ast_node *cmd)
{
	const t_exec_map	*exec_map = get_exec_map();

	while (exec_map->type)
	{
		if (exec_map->type == cmd->type)
			return (exec_map->f(shell, cmd));
		exec_map++;
	}
	perror("Unknown command type");
	return (NULL);
}

void	orchestrator(t_shell *shell)
{
	t_ast_node	*cmd;

	shell->exit_code = 0;
	cmd = find_next_cmd(shell->ast);
	while (cmd)
		cmd = handle_cmd(shell, cmd);
}

// ( ( ( echo 'salut' ) ) && echo 'bonjour' ) | echo bar | echo "sa va"