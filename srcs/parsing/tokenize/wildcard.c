#include "parsing.h"

static t_bool	is_a_wildcard(t_lexer_args * args, t_uint *current_type)
{
	if (*current_type == TEXT && !args->quote &&
		*args->input == SYMBOL_GLOB_ANY)
		return (TRUE);
	return (FALSE);
}

t_pointer	tokenize_wildcard(t_lexer_args *args, t_uint *current_type)
{
	if (FLAG_GLOBBING && is_a_wildcard(args, current_type))
		*current_type = WILDCARD;
	return (init_pointer(NULL, FALSE));
}
