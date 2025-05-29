/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:10:10 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/29 15:44:16 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"
#include "utils.h"
#include "libft_tree.h"
#include "parsing.h"
#include "ast.h"
#include "cmd_redir.h"


void	negate_wildcard(char **str);

static char *join_token(t_token *token, char *value, t_bool *is_wildcard)
{
	char	*tmp;
	t_token_type	type;

	type = token->type;
	if (type & WILDCARD)
		*is_wildcard = TRUE;
	if (type & (WILDCARD | TEXT))
		negate_wildcard(&token->value);
	tmp = ft_strjoin(value, token->value);
	free(value);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static t_dynarray	*join_word_tokens(t_shell *shell, t_dynarray *tokens, t_dynarray *args)
{
	t_token	*token;
	char	*value;
	t_bool  is_wildcard;
	t_uint	i;

	i = 0;
	value = ft_strdup("");
	if (!value)
		return (NULL);
	is_wildcard = FALSE;
	while (i < tokens->count)
	{
		token = get_dynarray_value(tokens, i);
		if (token->type == M_EOF || token->type == M_SPACE)
			value = save_expand_entry(shell, args, value, &is_wildcard);
		else
			value = join_token(token, value, &is_wildcard);
		if (!value)
			return (NULL);
		i++;
	}
	free(value);
	return (args);
}

/**
 * @brief Expands a word in the shell context.
 * 
 * This function checks if the word is an environment variable or a wildcard.
 *
 * @param shell The shell context containing environment variables.
 * @param word The word to be expanded, represented as a dynamic array.
 * @param args The array to store the expanded arguments.
 * 
 * @return The last args element or NULL if an error occurs.
*/
t_dynarray	*expand_word(t_shell *shell, t_dynarray *word, t_dynarray *args)
{
	t_lexer_args	lex;
	t_parse_status	status;
	char			*input;
	t_dynarray		*ret;
	
	if (!expand_env_word(shell, word))
		return (NULL);
	input = build_expand_input(word);
	if (!input)
		return (NULL);
	lex = init_lexer_args(input, FALSE);
	if (!lex.tokens.data)
		return (NULL);
	ret = NULL;
	status = lexer(&lex);
	free(input);
	if (status != MALLOC_ERROR)
		ret = join_word_tokens(shell, &lex.tokens, args);
	destroy_lexer_args(&lex);
	return (ret);
}
