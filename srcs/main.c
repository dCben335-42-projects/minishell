#include "messages.h"
#include "minishell.h"
#include "libft.h"
#include "builtin.h"
#include "errors.h"
#include "parser_lexer.h"
#include "map.h"
#include "cmd.h"

void	handle_command(t_shell *shell, char **args)
{
	const t_env	*node = get_env_node(shell->env, PATH_KEY);
	char		**paths;
	char		*path;
	char		*tmp;
	size_t		i;

	if (!s_ptr((void *)node, ERR_NOT_FOUND))
		return ;
	paths = ft_split(node->value, ':');
	if (!s_ptr((void *)paths, ERROR_MALLOC))
		return ;
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		tmp = path;
		if (path)
			path = ft_strjoin(path, args[0]);
		ft_handle_free((void **)&tmp);
		p_ptr((void *)path, ERROR_MALLOC);
		if (path && !access(path, F_OK) && execute_cmd(path, args))
			break ;
		free(path);
		i++;
	}
	ft_handle_free_split(paths);
}


static void handle_loop(t_shell *shell)
{
	//(void)shell;
	char		*input;
	//char		**args;

	//input = "bonjour sava bien";
	//command_handler(&input);
	while (TRUE)
	{
		input = readline(SHELL_NAME);
		//input = "bonjour sava bien";
		if (!input)
			break ;
		//free(input);
		command_handler(input);

		//if (*input)
		//	add_history(input);
		//args = ft_split(input, ' ');
		//if (args[0])
		//	if (!is_builtin(args, shell))
		//		handle_command(shell, args);
		//ft_handle_free_split(args);
		if (input)
			free(input);
		printf("exit code: %d\n", shell->exit_code);
	}
}

int main(int argc, char **argv, char **envp)
{
	const char	*exit_args[] = { "exit", NULL };    
	t_shell		shell;
	
	(void)argc;
	(void)argv;
	(void) &handle_loop;
	shell = init_shell(envp);
	init_signals();
	handle_loop(&shell);
	ft_exit(&shell, (char **)exit_args);
    return (0);
}