#include "parsing.h"

t_ptr	tokenize_operator(t_lexer_args *args,
	int offset, t_token_type type)
{
	t_ptr	pointer;

	if (type == R_HEREDOC)
		args->is_heredoc = HEREDOC;
	else if (type == R_HEREDOC_TRIM)
		args->is_heredoc = HEREDOC_TRIM;
	pointer = init_pointer(init_token(type, args->input, offset), TRUE);
	args->input += offset;
	return (pointer);
}
