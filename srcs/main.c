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

void command_handler_lexer(char **input, t_lexer_args *args);
void command_not_finished(t_lexer_args *args, char **input);

char **map_tokens(t_token *tokens, int token_count)
{
	char **tokens_value_map;
	int i;

	tokens_value_map = malloc(sizeof(char *) * token_count);
	i = 0;
	while (i < token_count)
	{
		tokens_value_map[i] = tokens[i].value;
		i++;
	}
	return (tokens_value_map);
}

void	execute_command(char **tokens)
{

    if (fork() == 0)
	{ 
		execvp(tokens[0], tokens);
		exit(1); 
	}
    wait(NULL);
}

void command_handler_lexer(char **input, t_lexer_args *args)
{
	char *error = NULL;
	t_parse_status status;

	args->input = *input;
	args->tokens = malloc(sizeof(t_token) * MAX_TOKENS);
	args->token_number_max = MAX_TOKENS;
	args->token_count = 0;

	status = lexer(args, &error);
	if (status == COMMAND_NOT_FINISHED)
	{
		command_not_finished(args, input);
		return ;
	}
	else if (status != COMMAND_VALID)
	{
		printf("Error: %s\n", error);
		free(error);
		return ;
	}
	else
	{
		print_tokens(args->tokens, args->token_count);
	}
	if (**input)
		add_history(*input);
	execute_command(map_tokens(args->tokens, args->token_count));
}

void command_not_finished(t_lexer_args *args, char **input)
{
	char *tmp2;
	char *tmp;
	int i;

	i = 0;
	tmp = readline(SHELL_NEXT_NAME);
	tmp2 = ft_strjoin(*input, tmp);
	free(tmp);
	free(*input);
	input = &tmp2;
	while (i < args->token_count)
	{
		free(args->tokens[i].value);
		i++;
	}
	free(args->tokens);
	command_handler_lexer(input, args);
}

int command_handler(char **input)
{
	t_lexer_args args;
	command_handler_lexer(input, &args);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;
    char	*input;
    
	shell = init_shell(envp);
    while (1)
	{
		input = readline(SHELL_NAME);
        if (!input)
			break;
		command_handler(&input);
    }
	destroy_shell(&shell);
	(void)argc;
	(void)argv;
    return (0);
}
