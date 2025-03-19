#include "parser_lexer.h"

/**
 * Concatène deux chaînes de caractères
 * @param dest: chaîne de destination
 * @param src: chaîne source
 */
size_t	ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (i);
}

/**
 * Vérifie si le token est un opérateur de contrôle
 * @param token: token à vérifier
 */
int	is_control_operator(t_token token)
{
	t_token_type	type;

	type = token.type;
	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR
		|| type == TOKEN_SEMICOL || type == TOKEN_BACKGROUND
		|| type == TOKEN_PIPE_ERR || type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT);
}

/**
 * Génère un message d'erreur
 * @param token: token invalide
 * @param error: message d'erreur
 */
t_parse_status	get_error_message(t_token *token, char **error)
{
	const size_t	msg_len
		= strlen("erreur de syntaxe près du symbole inattendu « ")
		+ strlen(token->value) + strlen(" »\n") + 1;

	*error = ft_calloc(msg_len, sizeof(char));
	ft_strcat(*error, "erreur de syntaxe près du symbole inattendu «\u00A0");
	ft_strcat(*error, token->value);
	ft_strcat(*error, "\u00A0»\n");
	destroy_token(token);
	return (COMMAND_NOT_VALID);
}

/**
 * Fonction pour analyser les tokens
 * @param args: arguments du lexer
 * @param token: token à analyser
 * @return le statut de la commande
 */
t_parse_status	token_parser(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (args->tokens.count == 0)
	{
		if (is_control_operator(*token))
			return(get_error_message(token, &args->error));
	}
	else
	{
	    prev_token = ((t_token *)get_value(&args->tokens, args->tokens.count - 1));

	    if (is_control_operator(*token) && is_control_operator(*prev_token))
	        return(get_error_message(token, &args->error));

	    if (prev_token->type == TOKEN_OPEN_BRACKET && token->type == TOKEN_CLOSE_BRACKET)
	        return(get_error_message(token, &args->error));

	    if (token->type == TOKEN_OPEN_BRACKET)
	        args->parenthesis.open++;
	    else if (token->type == TOKEN_CLOSE_BRACKET)
	        args->parenthesis.close++;
		
	    if (args->parenthesis.close > args->parenthesis.open)
	        return(get_error_message(token, &args->error));
	}
	set_value(&args->tokens, args->tokens.count, token);
	return (COMMAND_VALID);
}
