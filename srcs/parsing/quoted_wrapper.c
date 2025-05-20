#include "parsing.h"

t_uint quoted_wrapper(t_lexer_args *args, t_uint *current_type)
{
	if (args->quote)
	{
		if (*current_type == TEXT)
			*current_type = QUOTED_TEXT;
		else if (*current_type == EXPAND)
			*current_type = QUOTED_EXPAND;
	}
	return (*current_type);
}