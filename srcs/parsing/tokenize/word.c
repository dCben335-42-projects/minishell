#include "parsing.h"

t_ptr	tokenize_word(t_lexer_args *args)
{
	t_token_type	current_type;
	t_ptr			pointer;
	char			*start_i;

	start_i = (char *)args->input;
	current_type = TEXT;
	while (*args->input && (args->quote || !ft_isspace(*args->input))
		&& (args->quote || get_token_type(args->input, 0) == TEXT))
    {
		pointer = tokenize_enclosures(args, &start_i, &current_type);
		if (pointer.is_malloc)
			return (pointer);
		args->input++;
    }
	return (wrap_ptr_token(args, &current_type, &start_i, 0));
}
