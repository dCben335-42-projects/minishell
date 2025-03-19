#include "lexer_args.h"

void	*destroy_lexer_args(t_lexer_args *args)
{
	destroy_dynamic_array(&args->tokens);
	free(args->error);
	free((char *)args->input);
	return (NULL);
}
