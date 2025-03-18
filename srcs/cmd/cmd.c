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
#include "map.h"
#include "cmd.h"

void command_handler_lexer(char **input, t_lexer_args *args);
void command_not_finished(t_lexer_args *args, char **input);

char **map_tokens(t_dynamic_array *tokens)
{
	char	**tokens_value_map;
	t_uint	i;

	tokens_value_map = malloc(sizeof(char *) * (tokens->count + 1));
	i = 0;
	while (i < tokens->count)
	{
		tokens_value_map[i] = tokens->data[i];
		i++;
	}
	tokens_value_map[i] = NULL;
	return (tokens_value_map);
}

void command_handler_lexer(char **input, t_lexer_args *args)
{
	char *error = NULL;
	t_parse_status status;

	args->input = *input;
	args->tokens = init_dynamic_array(20, (void *(*)(void *))destroy_token);
	status = lexer(args, &error);
	if (status == COMMAND_NOT_FINISHED)
	{
		destroy_dynamic_array(&args->tokens);
		command_not_finished(args, input);
		return ;
	}
	if (status != COMMAND_VALID)
	{
		printf("Error: %s\n", error);
		free(error);
		return ;
	}
	print_tokens(&args->tokens);
	destroy_dynamic_array(&args->tokens);
	if (**input)
		add_history(*input);
	//execute_cmd(map_tokens(args->tokens));
}

void command_not_finished(t_lexer_args *args, char **input)
{
	char *tmp2;
	char *tmp;
	
	tmp = readline(SHELL_NEXT_NAME);
	tmp2 = ft_strjoin(*input, tmp);
	free(tmp);
	free(*input);
	*input = NULL;
	printf("tmp2: %s\n", tmp2);
	command_handler_lexer(&tmp2, args);
	free(tmp2);
}

int command_handler(char **input)
{
	t_lexer_args args;
	command_handler_lexer(input, &args);
	return (0);
}