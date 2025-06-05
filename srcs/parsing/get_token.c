#include "parsing.h"

t_ptr	get_token(t_lexer_args *args)
{
	int				op_len;
	t_token_type	type;

	op_len = 0;
	type = get_token_type(args->input, &op_len);
	if (type == TEXT || args->quote)
		return (tokenize_word(args));
    return (tokenize_operator(args, op_len, type));
}

t_bool	get_prev_token(t_lexer_args *args, t_token **prev_token)
{
	t_uint		count;

	count = args->tokens.count;
	if (count == 0)
		return (FALSE);
	*prev_token = get_dynarray_value(&args->tokens, count - 1);
	if ((*prev_token)->type & M_SPACE)
	{
		if (count < 2)
			return (FALSE);
		*prev_token = get_dynarray_value(&args->tokens, count - 2);
	}
	return (TRUE);
}

t_ptr	get_next_token(t_lexer_args *args)
{
	if (!*args->input)
		return (init_pointer(NULL, FALSE));
	if (args->quote == DELIMITER_EXPANDABLE_TEXT 
		&& *args->input == DELIMITER_EXPANDABLE_TEXT)
	{
		args->input++;
		args->quote = 0;
	}
	if (ft_isspace(*args->input) && !args->quote)
		return (tokenize_whitespace(args));
	return (get_token(args));
}