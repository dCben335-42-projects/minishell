#include "parser_lexer.h"

static t_bool	is_command_finished(const char *input, t_token *token)
{
	const t_token_type	type = token->type;

	if (type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_PIPE
		|| type == TOKEN_PIPE_ERR || type == TOKEN_EOF)
	{
		while (ft_isspace(*input))
			input++;
		if (*input == 0)
		{
			destroy_token(token);
			return (FALSE);
		}
	}
	return (TRUE);
}

static t_token	*get_token(t_lexer_args *args,
	size_t *i, int offset, t_token_type type)
{
	t_token	*token;

	if (type == TOKEN_QUOTE || type == TOKEN_DQUOTE)
		token = handler_token_quote(i, args, type);
	else if (type != TOKEN_TEXT)
		token = handler_token_operator(args, i, offset, type);
	else
		token = handler_token_text(i, args);
	return (token);
}

static t_parse_status	get_parsing_error_status(t_token *token,
	t_lexer_args *args, size_t *i)
{
	if (token == NULL)
		return (COMMAND_NOT_VALID);
	if (!is_command_finished(&args->input[*i], token))
		return (COMMAND_NOT_FINISHED);
	return (token_parser(args, token));
}

t_parse_status	lexer(t_lexer_args *args)
{
	size_t			i;
	int				offset;
	t_parse_status	status;
	t_token			*token;
	t_token_type	type;

	i = 0;
	while (args->input[i])
	{
		while (ft_isspace(args->input[i]))
			i++;
		offset = 0;
		type = get_token_type(&args->input[i], &offset);
		token = get_token(args, &i, offset, type);
		status = get_parsing_error_status(token, args, &i);
		if (status != COMMAND_VALID)
			return (status);
	}
	return (COMMAND_VALID);
}

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
