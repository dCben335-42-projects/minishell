#include "parsing.h"
#include "struct_env.h"


static t_bool	is_an_expand(t_lexer_args * args)
{
	const char cur_char = *args->input;
	const char next_char = *(args->input + 1);

	if (cur_char == SYMBOL_VAR_EXPAND 
		&& (ft_isalpha(next_char) || next_char == '_' || next_char == '?')
		&& (!args->quote || args->quote == DELIMITER_EXPANDABLE_TEXT))
		return (TRUE);
	if (cur_char == SYMBOL_VAR_EXPAND && !args->quote && (
			next_char == DELIMITER_EXPANDABLE_TEXT 
			|| next_char == DELIMITER_LITERAL_TEXT
		))
		return (TRUE);
	return (FALSE);
}



t_ptr	tokenize_expand(t_lexer_args *args, char **start_i, t_token_type *current_type)
{
	size_t		key_len;
	
	if (FLAG_VAR_EXPANSION && is_an_expand(args))
	{
		if (need_tokenize(args, start_i))
			return (wrap_ptr_token(args, current_type, start_i, 0));
		else
		{
			*current_type = EXPAND;
			key_len = parse_env_key_len(++args->input);
			if (key_len == 0)
				return (init_pointer(init_token(TEXT, *start_i, 0), TRUE));
			args->input += key_len;
			return (wrap_ptr_token(args, current_type, start_i, key_len + 1));
		}
	}
	return (init_pointer(NULL, FALSE));
}