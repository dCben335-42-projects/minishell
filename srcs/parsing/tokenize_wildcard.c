#include "parsing.h"

t_pointer	handler_wildcard(t_lexer_args *args, char **start_i, t_token_type_flags *current_type)
{
	if (FLAG_GLOBBING && is_a_wildcard(args, current_type))
			*current_type = TOKEN_WILDCARD;
	return (init_pointer(NULL, FALSE, FALSE));
}