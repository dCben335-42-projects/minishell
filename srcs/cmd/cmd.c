//#include "messages.h"
//#include "minishell.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
//#include <sys/wait.h>
//#include <readline/readline.h>
//#include <readline/history.h>
//#include "libft.h"
//#include "errors.h"
//#include "parsing.h"
//#include "struct_dynarray.h"
//#include "cmd.h"
//#include "ast.h"
//#include "orchestrator.h"

//void command_handler_lexer(char *input, t_lexer_args *args);
//void command_not_finished(t_lexer_args *args, char *input);

//void	print_tokens(t_dynarray *tokens)
//{
//	t_uint	i;
//	t_uint	count;
//	t_token	*data;

//	i = 0;
//	count = tokens->count;
//	while (i < count)
//	{
//		data = (t_token *)get_dynarray_value(tokens, i);
//		printf("Token: %-12s", data->value);
//		printf(" | ");
//		printf("Type: %s", get_token_type_name(data->type));
//		printf("\n==================================");
//		printf("==================================\n");
//		i++;
//	}
//}
//char **map_tokens(t_dynarray *tokens)
//{
//	char	**tokens_value_map;
//	t_uint	i;

//	tokens_value_map = malloc(sizeof(char *) * (tokens->count + 1));
//	i = 0;
//	while (i < tokens->count)
//	{
//		tokens_value_map[i] = tokens->data[i];
//		i++;
//	}
//	tokens_value_map[i] = NULL;
//	return (tokens_value_map);
//}

//void command_handler_lexer(char *input, t_lexer_args *args)
//{
//	t_parse_status status;

//	*args = init_lexer_args(input);
//	status = lexer(args);
//	if (status == COMMAND_NOT_FINISHED)
//	{
//		command_not_finished(args, input);
//		return ;
//	}
//	if (status != COMMAND_VALID)
//	{
//		printf("Error: %s\n", args->error);
//		return ;
//	}
//	print_tokens(&args->tokens);
//	if (*input)
//		add_history(input);
//	//execute_cmd(map_tokens(args->tokens));
//}

//void command_not_finished(t_lexer_args *args, char *input)
//{
//	char *new_input;
//	char *tmp;

//	tmp = readline(SHELL_NEXT_NAME);
//	new_input = ft_strjoin(input, tmp);
//	free(tmp);
//	destroy_lexer_args(args);
//	command_handler_lexer(new_input, args);
//}

//int command_handler(char *input, t_shell *shell)
//{
//	//t_dynarray		*cmd_master;
//	(void)shell;
//	t_lexer_args args;

//	command_handler_lexer(input, &args);
///* 	cmd_master = ast_builder(&args.tokens);
//	if (cmd_master)
//	{
//		print_ast_json_wrapper(cmd_master);
//		orchestrator(cmd_master);
//		destroy_dynamic_array(cmd_master);
//	}
//	destroy_lexer_args(&args); */
//	return (0);
//}
