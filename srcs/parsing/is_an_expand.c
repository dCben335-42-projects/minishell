#include "parsing.h"

t_bool	is_an_expand(t_lexer_args * args)
{
	if (*args->input == EXPAND_EXPR && ft_isalpha(*(args->input + 1)) && (args->quote == 0 || args->quote == DQUOTE))
		return (TRUE);
	return (FALSE);
}
