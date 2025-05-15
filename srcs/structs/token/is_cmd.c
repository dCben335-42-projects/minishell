#include "struct_token.h"

int is_cmd_token(t_token token)
{
	return (token.type & (
		get_lexer_token_def()->masks.redir |
		get_lexer_token_def()->masks.name |
		M_SPACE));
}