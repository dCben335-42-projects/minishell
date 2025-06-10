/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 03:34:24 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 03:34:38 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * 
 * @brief Tokenizes an operator based on its length and type.
 *
 * This function creates a token of the specified type and updates the input
 * pointer to skip over the operator.
 *
 * @param args The lexer arguments containing the input string and state.
 * @param op_len The length of the operator to tokenize.
 * @param type The type of the operator to create a token for.
 *
 * @return A pointer to the newly created token.
 * 
 */
t_ptr	tokenize_operator(
	t_lexer_args *args,
	int op_len,
	t_token_type type
)
{
	t_ptr	pointer;

	if (type == R_HEREDOC)
		args->is_heredoc = HEREDOC;
	else if (type == R_HEREDOC_TRIM)
		args->is_heredoc = HEREDOC_TRIM;
	pointer = init_pointer(init_token(type, args->input, op_len), TRUE);
	args->input += op_len;
	return (pointer);
}
