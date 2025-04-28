#include "parsing.h"

static t_pointer	handler_enclosure(t_lexer_args *args, char **start_i, t_token_type_flags *current_type, const char quote)
{
	if (*args->input == quote)
	{
		if (args->quote == 0)
		{
			args->quote = quote;
			if (args->input - *start_i > 0)
			{
				args->input++;
				return (init_pointer(
						init_token_p(*current_type, *start_i, args->input - *start_i - 1),
						TRUE, FALSE));
			}
			if (args->input - *start_i == 0)
				(*start_i)++;
		}
		else if (args->quote == quote)
		{
			args->quote = 0;
			if (args->input - *start_i > 0)
			{
				args->input++;
				return (init_pointer(
						init_token_p(*current_type, *start_i, args->input - *start_i - 1),
						TRUE, FALSE));
			}
		}
	}
	return (init_pointer(NULL, FALSE, FALSE));
}
static t_pointer	handler_enclosures(t_lexer_args *args, char **start_i, t_token_type_flags *current_type)
{
	t_pointer	pointer;

	pointer = handler_enclosure(args, start_i, current_type, DQUOTE);
	if (pointer.is_malloc)
		return (pointer);
	return (handler_enclosure(args, start_i, current_type, QUOTE));
}

static	t_pointer	handler_expand(t_lexer_args *args, char **start_i, t_token_type_flags *current_type)
{
	if (is_an_expand(args))
	{
		if (args->input - *start_i > 0)
			return (init_pointer(
						init_token_p(*current_type, *start_i, args->input - *start_i),
						TRUE, FALSE));
		else
		{
			*current_type = TOKEN_EXPAND;
			(*start_i)++;
		}
	}
	return (init_pointer(NULL, FALSE, FALSE));
}

static	t_pointer	handler_wildcard(t_lexer_args *args, char **start_i, t_token_type_flags *current_type)
{
	if(is_a_wildcard(args, current_type))
		*current_type = TOKEN_WILDCARD;
	return (init_pointer(NULL, FALSE, FALSE));
}

t_pointer	tokenize_enclosures(t_lexer_args *args, char **start_i, t_token_type_flags *current_type)
{
	t_pointer	pointer;

	pointer = handler_enclosures(args, start_i, current_type);
	if (pointer.is_malloc)
		return (pointer);
	pointer = handler_expand(args, start_i, current_type);
	if (pointer.is_malloc)
		return (pointer);
	return (handler_wildcard(args, start_i, current_type));
}