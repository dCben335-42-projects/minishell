#include "parsing.h"

t_pointer	tokenize_operator(t_lexer_args *args,
	int offset, t_uint type)
{
	t_pointer	pointer;

	pointer = init_pointer(init_token(type, args->input, offset), TRUE, FALSE);
	args->input += offset;
	return (pointer);
}