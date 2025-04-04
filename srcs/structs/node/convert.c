#include "node.h"

t_ast_node *convert_token_to_cmd(t_token *token)
{
	if (token->type == TOKEN_TEXT)
		return (init_node(CMD_TEXT, token->value));
	else if (token->type == TOKEN_VAR_TEXT)
		return (init_node(CMD_VAR_TEXT, token->value));
	else if (token->type == TOKEN_LITERAL_TEXT)
		return (init_node(CMD_LITERAL_TEXT, token->value));
	else if (token->type == TOKEN_PIPE)
		return (init_node(CMD_PIPE, NULL));
	else if (token->type == TOKEN_AND)
		return (init_node(CMD_AND, NULL));
	else if (token->type == TOKEN_OR)
		return (init_node(CMD_OR, NULL));
	else if (token->type == TOKEN_OPEN_BRACKET)
		return (init_node(CMD_PARENTHESIS_OPEN, NULL));
	else if (token->type == TOKEN_CLOSE_BRACKET)
		return (init_node(CMD_PARENTHESIS_CLOSE, NULL));
	else if (token->type == TOKEN_REDIR_IN)
		return (init_node(CMD_REDIR_IN, NULL));
	else if (token->type == TOKEN_REDIR_OUT)
		return (init_node(CMD_REDIR_OUT, NULL));
	else if (token->type == TOKEN_APPEND)
		return (init_node(CMD_APPEND, NULL));
	else if (token->type == TOKEN_HEREDOC)
		return (init_node(CMD_HEREDOC, NULL));
	else if (token->type == TOKEN_SPACE)
		return (init_node(CMD_SPACE, NULL));
	return (NULL);
}
