#include "parsing.h"

t_pointer	get_token(
	t_lexer_args *args,
	int offset,
	t_token_type_flags type
)
{
	if (type == TOKEN_TEXT)
		return (tokenize_word(args));
    return (tokenize_operator(args, offset, type));
}