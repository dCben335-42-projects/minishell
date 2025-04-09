#include "ast.h"
#include "dynamic_array.h"
#include "token.h"
#include <stdlib.h>
#include "parser_lexer.h"

t_dynamic_array	*ast_builder(t_dynamic_array *tokens)
{
	t_get_cmd_master	*cmd_master_params;
	t_dynamic_array		*cmd_master;
	t_bool				has_malloc_error;

	has_malloc_error = FALSE;
	cmd_master_params = init_t_get_cmd_master(
			tokens, 0, tokens->count - 1, &has_malloc_error);
	if (!cmd_master_params)
		return (NULL);
	cmd_master = get_cmd_master(cmd_master_params);
	free(cmd_master_params);
	if (cmd_master && has_malloc_error)
	{
		destroy_dynamic_array(cmd_master);
		return (NULL);
	}
	return (cmd_master);
}

//int	main(void)
//{
//	t_dynamic_array		*cmd_master;
//	t_dynamic_array		*tokens;
//	t_parse_status		status;
//	t_lexer_args		args;

//	const char *command = "( ( ( echo 'salut' ) ) && echo 'bonjour' )";

//	args = init_lexer_args(command);
//	status = lexer(&args);
//	if (status != COMMAND_VALID)
//	{
//		printf("Error: %s\n", (&args)->error);
//		return (0);
//	}
//	print_tokens(&(&args)->tokens);
//	printf("command=%s\n", command);
//	tokens = &args.tokens;
//	cmd_master = ast_builder(tokens);
//	if (!cmd_master)
//	{
//		destroy_dynamic_array(tokens);
//	}
//	else
//	{
//		print_ast_json_wrapper(cmd_master);
//		destroy_dynamic_array(cmd_master);
//		destroy_dynamic_array(tokens);
//	}
//    return (0);
//}

//cc srcs/ast_builder/*.c libs/libft/srcs/**/*.c 
//srcs/structs/**/*.c srcs/lexer/*.c -I includes -I libs/libft/includes