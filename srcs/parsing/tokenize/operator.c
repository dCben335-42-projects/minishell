#include "parsing.h"

t_pointer	tokenize_operator(t_lexer_args *args,
	int offset, t_uint type)
{
	t_pointer	pointer;

	if (type == R_HEREDOC)
		args->is_heredoc = HEREDOC;
	else if (type == R_HEREDOC_TRIM)
		args->is_heredoc = HEREDOC_TRIM;
	pointer = init_pointer(init_token(type, args->input, offset), TRUE);
	args->input += offset;
	return (pointer);
}
