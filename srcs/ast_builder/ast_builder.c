#include "ast.h"
#include <stdlib.h>

t_dynarray	*ast_builder(t_dynarray *tokens)
{
	t_get_cmd_master	*cmd_master_params;
	t_dynarray			*cmd_master;
	t_bool				has_malloc_error;

	has_malloc_error = FALSE;
	cmd_master_params = init_t_get_cmd_master(
			tokens, 0, tokens->count - 1, &has_malloc_error);
	if (!cmd_master_params)
		return (NULL);
	cmd_master = get_cmd_master(cmd_master_params);
	free(cmd_master_params);
	if (cmd_master && has_malloc_error)
	{
		destroy_dynarray(cmd_master);
		return (NULL);
	}
	return (cmd_master);
}
