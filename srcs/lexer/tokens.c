#include "parser_lexer.h"

/**
 * Fonction pour obtenir la table des opérateurs
 * @param i: index de la table
 */
t_op_table	get_operator_table(int i)
{
	static t_op_table	op_table[9] = {
	{'|', {{'|', TOKEN_OR}, {'&', TOKEN_PIPE_ERR}, {'\0', TOKEN_PIPE}}},
	{'&', {{'&', TOKEN_AND}, {'\0', TOKEN_BACKGROUND}}},
	{'>', {{'>', TOKEN_APPEND}, {'\0', TOKEN_REDIR_OUT}}},
	{'<', {{'\0', TOKEN_REDIR_IN}}},
	{';', {{'\0', TOKEN_SEMICOL}}},
	{'\'', {{'\0', TOKEN_QUOTE}}},
	{'"', {{'\0', TOKEN_DQUOTE}}},
	{'(', {{'\0', TOKEN_OPEN_BRACKET}}},
	{')', {{'\0', TOKEN_CLOSE_BRACKET}}}
	};

	return (op_table[i]);
}

/**
 * Fonction pour obtenir le nom du token
 * @param type: type de token
 */
char	*get_token_name(const t_token_type type)
{
	static char	*token_name[] = {
		"TEXT",
		"VAR_TEXT",
		"LITERAL_TEXT",
		"PIPE",
		"AND",
		"OR",
		"SEMICOL",
		"REDIR_IN",
		"REDIR_OUT",
		"APPEND",
		"BACKGROUND",
		"PIPE_ERR",
		"QUOTE",
		"DQUOTE",
		"BRACKET_LEFT",
		"BRACKET_RIGHT",
		"EOF"
	};

	return (token_name[type]);
}