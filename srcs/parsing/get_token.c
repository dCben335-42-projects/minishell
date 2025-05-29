#include "parsing.h"

t_bool	get_prev_token(t_lexer_args *args, t_token **prev_token)
{
	t_uint		count;

	count = args->tokens.count;
	if (count == 0)
		return (FALSE);
	*prev_token = get_dynarray_value(&args->tokens, count - 1);
	if ((*prev_token)->type & M_SPACE)
	{
		if (count < 2)
			return (FALSE);
		*prev_token = get_dynarray_value(&args->tokens, count - 2);
	}
	return (TRUE);
}

void *negate_wildcard(char **str);

t_ptr	get_token(t_lexer_args *args, int offset, t_token_type type)
{
	if (type == TEXT || args->quote)
		return (tokenize_word(args));
    return (tokenize_operator(args, offset, type));
}