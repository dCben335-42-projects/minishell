#include "parser_lexer.h"

/**
 * Fonction pour gérer les tokens entre guillemets
 * @param i: index de la chaîne d'entrée
 * @param len: longueur de la chaîne d'entrée
 * @param args: arguments du lexer
 * @param type: type de token
 */
t_token	*handler_token_quoted(size_t *i,
	t_lexer_args *args, t_token_type type)
{
	size_t	start_i;

	(*i)++;
	if (!args->input[*i])
		return (init_token(TOKEN_EOF, "", 0, 0));
	if (get_token_type(&args->input[*i], 0) == type)
	{
		(*i)++;
		return (init_token(TOKEN_TEXT, "", 0, 0));
	}
	start_i = *i;
	while (args->input[*i] && (start_i == *i
			|| get_token_type(&args->input[*i], 0) != type))
		(*i)++;
	if (!args->input[*i])
		return (init_token(TOKEN_EOF, "", 0, 0));
	(*i)++;
	if (type == TOKEN_QUOTE)
		return (init_token(TOKEN_LITERAL_TEXT, args->input, start_i, *i - start_i - 1));
	return (init_token(TOKEN_VAR_TEXT, args->input, start_i, *i - start_i - 1));
}

/**
 * Fonction pour gérer les tokens de texte
 * @param i: index de la chaîne d'entrée
 * @param args: arguments du lexer
 */
t_token	*handler_token_text(size_t *i, t_lexer_args *args)
{
	size_t	start_i;

	start_i = *i;
	while (args->input[*i] && !isspace(args->input[*i])
		&& get_token_type(&args->input[*i], 0) == TOKEN_TEXT)
		(*i)++;
	return (init_token(TOKEN_TEXT, args->input, start_i, *i - start_i));
}

//t_parse_status	quote_part_lexer(t_token_type type, size_t *i,
//	t_lexer_args *args, t_token **token)
//{
//	if (type == TOKEN_QUOTE || type == TOKEN_DQUOTE)
//	{
//		*token = handler_token_quoted(i, args, type);
//		printf("jojo=%s\n", (*token)->value);
//		if ((*token)->type == TOKEN_EOF)
//			return (COMMAND_NOT_FINISHED);
//	}
//	return (COMMAND_VALID);
//}

/**
 * Fonction pour analyser les tokens
 * @param args: arguments du lexer
 * @param error: message d'erreur
 */
t_parse_status	lexer(t_lexer_args *args, char **error)
{
	size_t			i;
	int				offset;
	t_parse_status	status;
	t_token			*token;
	t_token_type	type;

	i = 0;
	token_parser(args, error, init_token(TOKEN_TEXT, "init", 0, 0));
	while (args->input[i])
	{
		while (ft_isspace(args->input[i]))
			i++;
		offset = 0;
		type = get_token_type(&args->input[i], &offset);

		// BUG: quote_part_lexer ne modifie pas la valeur de token
		//if (quote_part_lexer(type, &i, args, &token) == COMMAND_NOT_FINISHED)
		//	return (COMMAND_NOT_FINISHED);

		if (type == TOKEN_QUOTE || type == TOKEN_DQUOTE)
		{
			token = handler_token_quoted(&i, args, type);
			if (token->type == TOKEN_EOF)
				return (COMMAND_NOT_FINISHED);
		}
		else if (type != TOKEN_TEXT)
		{
			token = init_token(type, args->input, i, offset + 1);
			i += (offset + 1);
		}
		else
			token = handler_token_text(&i, args);
		if (token == NULL)
			return (COMMAND_NOT_VALID);
		status = token_parser(args, error, token);
		if (status != COMMAND_VALID)
			return (status);
	}
	return (COMMAND_VALID);
}

/**
 * Fonction pour afficher les tokens
 * @param tokens: tableau de tokens
 */
void	print_tokens(t_dynamic_array *tokens)
{
	t_uint	i;
	t_uint	count;
	t_token	*data;

	i = 0;
	count = tokens->count;
	while (i < count)
	{
		data = (t_token *)get_value(tokens, i);
		printf("Token: %-12s | Type: %s\n", data->value,
			get_token_type_name(data->type));
		i++;
	}
}
