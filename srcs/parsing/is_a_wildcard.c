#include "parsing.h"

t_bool	is_a_wildcard(t_lexer_args * args, t_token_type_flags *current_type)
{
	if (*current_type == TOKEN_TEXT && !args->quote && *args->input == WILDCARD_EXPR)
		return (TRUE);
	return (FALSE);
}