#include "parsing.h"

t_uint quoted_wrapper(t_lexer_args *args, t_uint *current_type)
{
	printf("ok\n");
	if (args->quote)
	{
		printf("ok2\n");
		if (*current_type == TEXT)
			*current_type = QUOTED_TEXT;
		else if (*current_type == EXPAND)
			*current_type = QUOTED_EXPAND;
	}
	return (*current_type);
}