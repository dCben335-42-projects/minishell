/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:18:18 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 18:25:51 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_lexer_args.h"

t_lexer_args	init_lexer_args(const char *input)
{
	t_lexer_args	args;

	args.base_input = (char *) input;
	args.input = input;
	args.error = NULL;
	args.quote = 0;
	args.start = input;
	args.input_size = ft_strlen(input);
	args.parenthesis = (t_bracket){0, 0};
	args.is_heredoc = NOT_HEREDOC;
	args.bracket = (t_bracket){0, 0};
	args.tokens = init_dynarray(5, (void *(*)(void *))destroy_token);
	args.right_operand = UNDEFINED;
	return (args);
}
