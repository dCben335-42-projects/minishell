#include "parsing.h"

t_token_type	quoted_wrapper(t_lexer_args *args, t_token_type *current_type)
{
	if (args->quote)
	{
		if (*current_type == TEXT)
			*current_type = QUOTED_TEXT;
		else if (*current_type == EXPAND)
			*current_type = QUOTED_EXPAND;
	}
	return (*current_type);
}


t_bool need_tokenize(t_lexer_args *args, char **start_i)
{
	return (args->input - *start_i > 0);
}

t_ptr wrap_ptr_token(t_lexer_args *args, t_token_type *current_type, char **start_i, size_t optional_len)
{
	t_token			*token;
	t_token_type	type;

	type = quoted_wrapper(args, current_type);
	if (!optional_len)
		optional_len = args->input - *start_i;
	token = init_token(type, *start_i, optional_len);
	return (init_pointer(token, TRUE));
}