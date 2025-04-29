#include "parsing.h"

t_pointer	tokenize_word(t_lexer_args *args)
{
	char				*start_i;
    t_token_type_flags	current_type;
	t_pointer			pointer;

	start_i = (char *)args->input;
	current_type = TOKEN_TEXT;
	while (*args->input && (args->quote || !ft_isspace(*args->input))
		&& get_token_type(args->input, 0) == TOKEN_TEXT)
    {
		pointer = tokenize_enclosures(args, &start_i, &current_type);
		if (pointer.is_malloc)
			return (pointer);
		args->input++;
    }
	return (init_pointer(init_token_p(current_type, start_i, args->input - start_i), TRUE, FALSE));
}