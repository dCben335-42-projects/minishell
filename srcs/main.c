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
#include "parser_lexer.h"

void	execute_command(char **args)
{
    if (fork() == 0) 
	{ 
		execvp(args[0], args);
		exit(1); 
	}
    wait(NULL);
}

char	**create_args(char *input)
{
	char	**args;

	args = ft_split(input, ' ');
	if (!args)
		error_malloc(NULL, NULL);
	return (args);
}

void command_handler(char *input)
{
	t_lexer_args args;

	args.input = input;
	args.tokens = NULL;
	args.token_count = 0;
	lexer(args);
}

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;
    char	*input;
	char	**args;
    
	shell = init_shell(envp);
    while (1)
	{
		input = readline(SHELL_NAME);
        if (!input)
			break;
        if (*input)
			add_history(input);
		command_handler(input);
		args = create_args(input);
		if (args[0])
			if (!is_builtin(args, &shell))
				printf("Command not found\n");
		ft_handle_free_split(args);
        free(input);
    }
	destroy_shell(&shell);
	(void)argc;
	(void)argv;
    return (0);
}
