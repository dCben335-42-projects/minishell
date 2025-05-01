#include "struct_token.h"

int is_cmd_token(t_token token)
{
	return (token.type & (
		E_REDIR_OPERATOR_MASK |
		E_TOKEN_NAME_MASK |
		SPACE));
}