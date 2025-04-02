#include "ast.h"
#include "dynamic_array.h"
#include "token.h"
#include <stdlib.h>
#include "parser_lexer.h"

int main() {
	t_dynamic_array	*cmd_master;
	t_dynamic_array *tokens;
	t_parse_status status;
	t_lexer_args args;

	//const char *command = "(ls | cat | ba && co | ga) | cat | josd | ls";
	const char *command = "(ls | cat | ba << co | ga) | cat | josd | ls";
	
	//args = init_lexer_args("true || (echo 'A' && echo 'B')");
	//args = init_lexer_args("ls -l && echo 'hello' && cat file.txt | output.txt && echo 'jojo' || echo 'tata'");
	//args = init_lexer_args("ls -l && echo 'hello' && cat file.txt | output.txt | momo.txt && echo 'jojo' || echo 'tata'");
	//args = init_lexer_args("dzidziu\"$PATH\""); // ajouter les espaces au token
	//args = init_lexer_args("echo \"bonjour\" && ( echo \"jojo\" && echo \"pipi\" ) || cat file.txt | output.txt | momo.txt | toto.txt | jiji.txt && echo \"jojo\" && echo \"toto\"");
	//args = init_lexer_args("echo \"bonjour\" && ( echo \"jojo\" || ( echo \"lord\" && echo \"dart\" ) && (echo \"pipi\") )" );
	//args = init_lexer_args("( echo \"bonjour\" &&  echo \"jojo\" )");
	//args = init_lexer_args("( ls && cat file.txt && echo 'hello') || (echo 'jojo' && echo 'tata' && (echo 'toto' 'tata'))");
	//args = init_lexer_args("echo \"bonjour\"");

	args = init_lexer_args(command);
	status = lexer(&args);
	if (status != COMMAND_VALID)
	{
		printf("Error: %s\n", (&args)->error);
		return (0);
	}
	print_tokens(&(&args)->tokens);
	printf("command=%s\n", command);
	tokens = &args.tokens;
	cmd_master = get_cmd_master((t_get_cmd_master){tokens, 0, tokens->count - 1});
	print_ast_json_wrapper(cmd_master);
    return (0);
}

//cc srcs/ast_builder/*.c libs/libft/srcs/**/*.c srcs/structs/**/*.c srcs/lexer/*.c -I includes -I libs/libft/includes