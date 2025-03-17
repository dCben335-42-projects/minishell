#include "parser_lexer.h"

/**
 * Fonction pour trouver le type de token
 * @param input: chaîne d'entrée
 * @param offset: décalage pour le prochain caractère
 */
t_token_type	find_token_type(const char *input, int *offset)
{
	int			i;
	int			j;
	t_op_table	op_table;

	i = 0;
	j = 0;
	while (i < OP_TABLE_SIZE)
	{
		op_table = get_operator_table(i++);
		if (op_table.key == input[0])
		{
			while (j < OP_TABLE_MAX_BRANCH)
			{
				if (op_table.transitions[j].next_char == '\0'
					|| op_table.transitions[j].next_char == input[1])
				{
					if (op_table.transitions[j].next_char != '\0')
						(*offset)++;
					return (op_table.transitions[j].type);
				}
				j++;
			}
		}
	}
	return (TOKEN_TEXT);
}

/**
 * Fonction pour gérer les tokens entre guillemets
 * @param i: index de la chaîne d'entrée
 * @param len: longueur de la chaîne d'entrée
 * @param args: arguments du lexer
 * @param type: type de token
 */
t_token	handler_token_quoted(int *i, int len,
	t_lexer_args *args, t_token_type type)
{
	int	start_i;

	(*i)++;
	start_i = *i;
	while (*i < len && (start_i == *i
			|| find_token_type(&args->input[*i], 0) != type))
		(*i)++;
	if (*i >= len)
		return ((t_token){TOKEN_EOF, NULL});
	(*i)++;
	if (type == TOKEN_QUOTE)
		return ((t_token){TOKEN_LITERAL_TEXT, ft_substr(args->input, start_i, *i - start_i - 1)});
	else
		return ((t_token){TOKEN_VAR_TEXT, ft_substr(args->input, start_i, *i - start_i - 1)});
}

t_token handler_token_text(int *i, int len, t_lexer_args *args)
{
	int	start_i;

	start_i = *i;
	while (*i < len && !isspace(args->input[*i]) && find_token_type(&args->input[*i], 0) == TOKEN_TEXT)
		(*i)++;
	return ((t_token){TOKEN_TEXT, ft_substr(args->input, start_i, *i - start_i)});
}

/**
 * Fonction pour analyser les tokens
 * @param args: arguments du lexer
 * @param error: message d'erreur
 */
t_parse_status	lexer(t_lexer_args *args, char **error)
{
	int				i;
	int				len;
	int				offset;
	t_parse_status	status;
	t_token			token;
	t_token_type	type;

	token_parser(args, error, (t_token){TOKEN_EOF, "init"});
	i = 0;
	len = ft_strlen(args->input);
	while (i < len)
	{
		while (isspace(args->input[i]))
			i++;
		offset = 0;
		type = find_token_type(&args->input[i], &offset);
		if (type == TOKEN_QUOTE || type == TOKEN_DQUOTE)
		{
			token = handler_token_quoted(&i, len, args, type);
			if (token.type == TOKEN_EOF)
				return (COMMAND_NOT_FINISHED);
		}
		else if (type != TOKEN_TEXT)
		{
			token = (t_token){type, ft_substr(args->input, i, offset + 1)};
			i += (offset + 1);
		}
		else
			token = handler_token_text(&i, len, args);
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
			get_token_name(data->type));
		i++;
	}
}
