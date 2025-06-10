/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subshell_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:32:36 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/10 22:18:16 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_token	*get_dynarray_values(t_dynarray *arr, int count)
{
	if (count < 0)
		return (NULL);
	return (get_dynarray_value(arr, count));
}

static t_bool	check_is_redir(t_lexer_args *args, t_token *token)
{
	t_token		*prev;
	int			count;

	count = args->tokens.count;
	prev = token;
	if (prev && prev->type & M_SPACE)
		prev = get_dynarray_values(&args->tokens, --count);
	while (prev && is_text_token(prev))
		prev = get_dynarray_values(&args->tokens, --count);
	if (prev && prev->type & M_SPACE)
		prev = get_dynarray_values(&args->tokens, --count);
	if (!prev)
		return (FALSE);
	return (is_redir_token(prev));
}

static t_bool	is_in_redir(t_token *prev)
{
	return (prev && (is_redir_token(prev) || prev->type & M_SPACE
			|| is_text_token(prev)));
}

t_parse_status	check_subshell_redir(t_lexer_args *args, t_token *token)
{
	int		count;
	t_token	*prev;

	count = args->tokens.count;
	if (!is_text_token(token) || check_is_redir(args, token))
		return (COMMAND_VALID);
	prev = token;
	while (is_in_redir(prev))
	{
		prev = get_dynarray_values(&args->tokens, --count);
		if (prev && prev->type & M_SPACE)
			prev = get_dynarray_values(&args->tokens, --count);
		while (prev && is_text_token(prev))
			prev = get_dynarray_values(&args->tokens, --count);
		if (prev && prev->type & M_SPACE)
			prev = get_dynarray_values(&args->tokens, --count);
		if (!prev || !is_redir_token(prev))
			return (COMMAND_VALID);
		prev = get_dynarray_values(&args->tokens, --count);
		if (prev && prev->type & M_SPACE)
			prev = get_dynarray_values(&args->tokens, --count);
	}
	if (!prev || !(prev->type & OP_PARENTHESIS_CLOSE))
		return (COMMAND_VALID);
	return (print_error_message(token, "err_no_right_operand"));
}
