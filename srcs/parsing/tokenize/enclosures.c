#include "parsing.h"

static t_ptr	return_token(t_lexer_args *args, char **start_i, t_token_type *current_type, const char quote)
{
	t_ptr	pointer;

	args->input++;
	pointer = init_pointer(init_token(
		quoted_wrapper(args, current_type), *start_i, args->input - *start_i - 1),
			TRUE);
	if (args->quote == quote)
		args->quote = 0;
	else
		args->quote = quote;
	return (pointer);
}

static t_ptr	handler_enclosure(t_lexer_args *args, char **start_i, t_token_type *current_type, const char quote)
{
	if (*args->input == quote)
	{
		if (args->quote == 0)
		{
			if (need_tokenize(args, start_i))
				return (return_token(args, start_i, current_type, quote));
			args->quote = quote;
			(*start_i)++;
		}
		else if (args->quote == quote)
		{
			if (need_tokenize(args, start_i))
				return (return_token(args, start_i, current_type, quote));
			args->quote = 0;
		}
	}
	return (init_pointer(NULL, FALSE));
}

static t_bool is_directly_closed(const char *input, const char quote)
{
	if (!quote && *input == DELIMITER_EXPANDABLE_TEXT && *(input + 1) == DELIMITER_EXPANDABLE_TEXT)
		return (TRUE);
	if (!quote  && *input == DELIMITER_LITERAL_TEXT && *(input + 1) == DELIMITER_LITERAL_TEXT)
		return (TRUE);
	return (FALSE);
}

static t_ptr	handler_enclosures(t_lexer_args *args, char **start_i, t_token_type *current_type)
{
	t_ptr	pointer;

	if (is_directly_closed(args->input, args->quote))
	{
		if (need_tokenize(args, start_i))
			return (wrap_ptr_token(args, current_type, start_i, 0));
		args->input += 2;
		return (init_pointer(init_token(QUOTED_TEXT, NULL, 0), TRUE));
	}
	pointer = handler_enclosure(args, start_i, current_type, DELIMITER_EXPANDABLE_TEXT);
	if (pointer.is_malloc)
		return (pointer);
	return (handler_enclosure(args, start_i, current_type, DELIMITER_LITERAL_TEXT));
}

t_ptr	tokenize_enclosures(t_lexer_args *args, char **start_i, t_token_type *current_type)
{
	t_ptr	ptr;

	ptr = handler_enclosures(args, start_i, current_type);
	if (ptr.is_malloc)
		return (ptr);
	ptr = tokenize_expand(args, start_i, current_type);
	if (ptr.is_malloc)
		return (ptr);
	return (tokenize_wildcard(args, current_type));
}
