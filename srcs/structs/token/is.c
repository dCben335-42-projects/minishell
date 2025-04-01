#include "token.h"

int	is_operator_token(t_token token)
{
	t_token_type	type;

	type = token.type;
	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR
		|| type == TOKEN_SEMICOL || type == TOKEN_BACKGROUND
		|| type == TOKEN_PIPE_ERR);
}

int is_text_token(t_token token)
{
	t_token_type	type;

	type = token.type;
	return (type == TOKEN_TEXT || type == TOKEN_VAR_TEXT
		|| type == TOKEN_LITERAL_TEXT);
}

int is_redir_token(t_token token)
{
	t_token_type	type;

	type = token.type;
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}
