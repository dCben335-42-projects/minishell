#include "parsing.h"

t_pointer	handler_expand(t_lexer_args *args, char **start_i, t_token_type_flags *current_type)
{
	if (FLAG_VAR_EXPANSION && is_an_expand(args))
	{
		if (args->input - *start_i > 0)
			return (init_pointer(
						init_token_p(*current_type, *start_i, args->input - *start_i),
						TRUE, FALSE));
		else
		{
			*current_type = TOKEN_EXPAND;
			(*start_i)++;
		}
	}
	else if (FLAG_VAR_EXPANSION && *current_type == TOKEN_EXPAND && !ft_isalpha(*args->input))
		return (init_pointer(init_token_p(*current_type, *start_i, args->input - *start_i), TRUE, FALSE));
	return (init_pointer(NULL, FALSE, FALSE));
}