#include "parsing.h"
#include "struct_env.h"

t_pointer	handler_expand(t_lexer_args *args, char **start_i, t_uint *current_type)
{
	size_t		key_len;
	if (FLAG_VAR_EXPANSION && is_an_expand(args))
	{
		if (args->input - *start_i > 0){
			return (init_pointer(
						init_token(quoted_wrapper(args, current_type), *start_i, args->input - *start_i),
						TRUE, FALSE));
		}
		else
		{
			*current_type = EXPAND;
			key_len = parse_env_key_len(++args->input);
			args->input += key_len;
			return (init_pointer(
						init_token(quoted_wrapper(args, current_type), *start_i, key_len + 1),
						TRUE, FALSE));
		}
	}
	return (init_pointer(NULL, FALSE, FALSE));
}