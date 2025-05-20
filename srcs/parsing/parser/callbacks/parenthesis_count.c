#include "parsing.h"

t_parse_status	increment_parenthesis_open(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->parenthesis.open++;
	return (COMMAND_VALID);
}

t_parse_status	increment_parenthesis_close(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->parenthesis.close++;
	return (COMMAND_VALID);
}
