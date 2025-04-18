#include "parser_lexer.h"

static t_bool	is_command_finished(const char *input, t_token *token)
{
	const t_token_type	type = token->type;

	if (type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_PIPE
		|| type == TOKEN_PIPE_ERR || type == TOKEN_UNKNOWN)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			return (FALSE);
	}
	return (TRUE);
}

static t_token	*get_token(t_lexer_args *args,
	size_t *i, int offset, t_token_type type)
{
	if (type == TOKEN_QUOTE || type == TOKEN_DQUOTE)
		return (handler_token_quote(i, args, type));
	if (type == TOKEN_TEXT)
		return (handler_token_text(i, args));
	return (handler_token_operator(args, i, offset, type));
}

static t_parse_status	get_parsing_error_status(t_token *token,
	t_lexer_args *args, size_t *i)
{
	t_parse_status	status; 

	if (token == NULL)
		return (COMMAND_NOT_VALID);
	status = token_parser(args, token);
	if (status != COMMAND_VALID)
		return (status);
	if (!is_command_finished(&args->input[*i], token))
		return (COMMAND_NOT_FINISHED);
	return (status);
}

static t_token *get_isspace_token(t_lexer_args *args, size_t *i)
{
	while (ft_isspace(args->input[*i]))
		(*i)++;
	return (init_token(TOKEN_SPACE, "", 0, 0));
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
		if (ft_isspace(args->input[i]))
		{
			token = get_isspace_token(args, &i);
			status = get_parsing_error_status(token, args, &i);
			if (status != COMMAND_VALID)
				return (status);
		}
		offset = 0;
		type = get_token_type(&args->input[i], &offset);
		token = get_token(args, &i, offset, type);
		status = get_parsing_error_status(token, args, &i);
		if (status != COMMAND_VALID)
			return (status);
	}
	return (get_parsing_error_status(init_token(TOKEN_EOF, "", 0, 0), args, &i));
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
