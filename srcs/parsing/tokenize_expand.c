#include "parsing.h"

t_pointer	handler_expand(t_lexer_args *args, char **start_i, t_uint *current_type)
{
	printf("STR: %s; STR2: %s\n", args->input, *start_i);

	if (FLAG_VAR_EXPANSION && is_an_expand(args))
	{
		printf("is_an_expand(args) == TRUE\n");
		if (args->input - *start_i > 0){
			printf("args->input - *start_i > 0\n");
			return (init_pointer(
						init_token(quoted_wrapper(args, current_type), *start_i, args->input - *start_i),
						TRUE, FALSE));
		}
		else
		{
			*current_type = EXPAND;
			//(*start_i)++; Pour avoir les $ dans la value de l'expand
		}
	}
	else if (FLAG_VAR_EXPANSION && *current_type == EXPAND && !ft_isalpha(*args->input))
	{
		printf("is_an_expand(args) == FALSE\n");
		return (init_pointer(init_token(quoted_wrapper(args, current_type), *start_i, args->input - *start_i), TRUE, FALSE));
	}
	printf("tg\n");
	return (init_pointer(NULL, FALSE, FALSE));
}