#include "parsing.h"

t_pointer	handler_wildcard(t_lexer_args *args, t_uint *current_type)
{
	if (FLAG_GLOBBING && is_a_wildcard(args, current_type))
			*current_type = WILDCARD;
	return (init_pointer(NULL, FALSE, FALSE));
}