#include "lexer_args.h"
#include "token.h"

t_lexer_args	init_lexer_args(const char *input)
{
	t_lexer_args	args;

	args.input = input;
	args.error = NULL;
	args.parenthesis = (t_bracket){0, 0};
	args.bracket = (t_bracket){0, 0};
	args.tokens = init_dynamic_array(40, (void *(*)(void *))destroy_token);
	return (args);
}
