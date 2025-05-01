#include "ast.h"
#include <stdlib.h>

t_dynarray	*ast_builder(t_dynarray *tokens)
{
	t_get_cmd_master	cmd_master_params;
	t_dynarray			*cmd_master;

	cmd_master_params = init_t_get_cmd_master(tokens, 0, tokens->count - 1);
	cmd_master = get_cmd_master(&cmd_master_params);
	if (cmd_master && cmd_master_params.has_malloc_error)
		destroy_dynarray(cmd_master);
	return (cmd_master);
}
