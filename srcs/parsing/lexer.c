/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:15:03 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/28 14:40:28 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	is_command_finished(const char *input, t_token *token)
{
	const t_token_type_flags	type = token->type;

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

static t_token	*get_token(
	t_lexer_args *args,
	size_t *i,
	int offset,
	t_token_type_flags type
)
{
	if (type == TOKEN_QUOTE || type == TOKEN_DQUOTE)
		return (handler_token_quote(i, args, type));
	if (type == TOKEN_TEXT)
		return (handler_token_text(i, args));
	return (handler_token_operator(args, i, offset, type));
}

static t_parse_status	get_parsing_error_status(
	t_token *token,
	t_lexer_args *args,
	size_t *i
)
{
	t_parse_status	status;

	if (!token)
		return (COMMAND_NOT_VALID);
	status = token_parser(args, token);
	if (status != COMMAND_VALID)
		return (status);
	if (!is_command_finished(&args->input[*i], token))
		return (COMMAND_NOT_FINISHED);
	return (status);
}

static t_token	*get_isspace_token(t_lexer_args *args, size_t *i)
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
	t_token_type_flags	type;

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
	token = init_token(TOKEN_EOF, "", 0, 0);
	return (get_parsing_error_status(token, args, &i));
}
