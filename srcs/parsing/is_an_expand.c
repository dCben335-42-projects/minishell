#include "parsing.h"

t_bool	is_an_expand(t_lexer_args * args)
{
	if (*args->input == SYMBOL_VAR_EXPAND && ft_isalpha(*(args->input + 1)) && (!args->quote || args->quote == DELIMITER_EXPANDABLE_TEXT))
		return (TRUE);
	return (FALSE);
}
