#include "parsing.h"

t_pointer	tokenize_operator(t_lexer_args *args,
	int offset, t_uint type)
{
	t_pointer	pointer;

	if (type == R_HEREDOC || type == R_HEREDOC_TRIM)
		args->is_heredoc = type;
	pointer = init_pointer(init_token(type, args->input, offset), TRUE, FALSE);

	args->input += offset;
	return (pointer);
}
