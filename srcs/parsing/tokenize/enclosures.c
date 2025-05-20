#include "parsing.h"

static t_pointer	return_token(t_lexer_args *args, char **start_i, t_uint *current_type, const char quote)
{
	t_pointer	pointer;

	args->input++;
	pointer = init_pointer(
			init_token(quoted_wrapper(args, current_type), *start_i, args->input - *start_i - 1),
			TRUE);
	if (args->quote == quote)
		args->quote = 0;
	else
		args->quote = quote;
	return (pointer);
}

static t_pointer	handler_enclosure(t_lexer_args *args, char **start_i, t_uint *current_type, const char quote)
{
	if (*args->input == quote)
	{
		if (args->quote == 0)
		{
			if (args->input - *start_i > 0)
				return (return_token(args, start_i, current_type, quote));
			args->quote = quote;
			if (args->input - *start_i == 0)
				(*start_i)++;
		}
		else if (args->quote == quote)
		{
			if (args->input - *start_i > 0)
				return (return_token(args, start_i, current_type, quote));
			args->quote = 0;
		}
	}
	return (init_pointer(NULL, FALSE));
}

static t_bool is_directly_closed(const char *input, const char quote)
{
	if (!quote && *input == DELIMITER_EXPANDABLE_TEXT && *(input + 1) == DELIMITER_LITERAL_TEXT)
		return (TRUE);
	else if (!quote  && *input == DELIMITER_LITERAL_TEXT && *(input + 1) == DELIMITER_EXPANDABLE_TEXT)
		return (TRUE);
	return (FALSE);
}

static t_pointer	handler_enclosures(t_lexer_args *args, char **start_i, t_uint *current_type)
{
	t_pointer	pointer;

	if (is_directly_closed(args->input, args->quote))
	{
		args->input += 2;
		return (init_pointer(init_token(QUOTED_TEXT, NULL, 0), TRUE));
	}
	pointer = handler_enclosure(args, start_i, current_type, DELIMITER_EXPANDABLE_TEXT);
	if (pointer.is_malloc)
		return (pointer);
	return (handler_enclosure(args, start_i, current_type, DELIMITER_LITERAL_TEXT));
}

t_pointer	tokenize_enclosures(t_lexer_args *args, char **start_i, t_uint *current_type)
{
	t_pointer	pointer;

	pointer = handler_enclosures(args, start_i, current_type);
	if (pointer.is_malloc)
		return (pointer);
	pointer = tokenize_expand(args, start_i, current_type);
	if (pointer.is_malloc)
		return (pointer);
	return (tokenize_wildcard(args, current_type));
}
