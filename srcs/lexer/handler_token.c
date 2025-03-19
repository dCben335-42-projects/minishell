#include "parser_lexer.h"

t_token	*handler_token_quote(size_t *i,
	t_lexer_args *args, t_token_type type)
{
	size_t	start_i;

	(*i)++;
	if (!args->input[*i])
		return (init_token(TOKEN_EOF, "", 0, 0));
	if (get_token_type(&args->input[*i], 0) == type)
	{
		(*i)++;
		return (init_token(TOKEN_TEXT, "", 0, 0));
	}
	start_i = *i;
	while (args->input[*i] && (start_i == *i
			|| get_token_type(&args->input[*i], 0) != type))
		(*i)++;
	if (!args->input[*i])
		return (init_token(TOKEN_EOF, "", 0, 0));
	(*i)++;
	if (type == TOKEN_QUOTE)
		return (init_token(TOKEN_LITERAL_TEXT,
				args->input, start_i, *i - start_i - 1));
	return (init_token(TOKEN_VAR_TEXT, args->input, start_i, *i - start_i - 1));
}

t_token	*handler_token_text(size_t *i, t_lexer_args *args)
{
	size_t	start_i;

	start_i = *i;
	while (args->input[*i] && !ft_isspace(args->input[*i])
		&& get_token_type(&args->input[*i], 0) == TOKEN_TEXT)
		(*i)++;
	return (init_token(TOKEN_TEXT, args->input, start_i, *i - start_i));
}

t_token	*handler_token_operator(t_lexer_args *args,
	size_t *i, int offset, t_token_type type)
{
	t_token	*token;

	token = init_token(type, args->input, *i, offset);
	*i += offset;
	return (token);
}
