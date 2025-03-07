#include "messages.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "errors.h"

void execute_command(char **args) {
    if (fork() == 0) 
	{ 
		execvp(args[0], args);
		exit(1); 
	}
    wait(NULL);
}

char **create_args(char *input)
{
	char **args;

	args = ft_split(input, ' ');
	if (!args)
		error_malloc(NULL, NULL);
	return (args);
}
int main(int argc, char **argv, char **envp)
{

	t_shell	shell;
    char	*input;
	char	**args;
    
	shell.env = create_envs(envp);
    while (1)
	{
		input = readline(SHELL_NAME);
        if (!input) 
			break;
        if (*input) 
			add_history(input);
		args = create_args(input);
		if (args[0])
			if (!is_builtin(args, &shell))
				printf("Command not found\n");
		ft_handle_free_split(args);
        free(input);
    }
	destroy_env(shell.env);
    return (0);
	(void)argc;
	(void)argv;
}
