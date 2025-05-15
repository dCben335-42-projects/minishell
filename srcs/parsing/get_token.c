#include "parsing.h"

t_pointer	get_token(
	t_lexer_args *args,
	int offset,
	t_uint type
)
{
	if (type == TEXT)
		return (tokenize_word(args));
    return (tokenize_operator(args, offset, type));
}