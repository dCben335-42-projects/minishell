#include "messages.h"
#include "minishell.h"
#include "libft.h"
#include "builtin.h"
#include "errors.h"
#include "parser_lexer.h"
#include "map.h"

t_bool	execute_command(char *path, char **args)
{
    if (fork() == 0) 
	{ 
		execve(path, args, NULL);
		free(path);
		exit(1); 
	}
    waitpid(-1, NULL, 0);
	free(path);
	return (TRUE);
}

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
		if (path && !access(path, F_OK) && execute_command(path, args))
			break ;
		free(path);
		i++;
	}
	ft_handle_free_split(paths);
}


static void handle_loop(t_shell *shell)
{
	char		*input;
	char		**args;

	while (TRUE)
	{
		input = readline(SHELL_NAME);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		args = ft_split(input, ' ');
		if (args[0])
			if (!is_builtin(args, shell))
				handle_command(shell, args);
		ft_handle_free_split(args);
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