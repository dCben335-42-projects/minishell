/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:18:18 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/28 12:54:31 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_lexer_args.h"

t_lexer_args	init_lexer_args(const char *input)
{
	t_lexer_args	args;

	
	args.input = input;
	args.error = NULL;
	args.quote = 0;
	args.start = input;
	args.input_size = ft_strlen(input);
	args.parenthesis = (t_bracket){0, 0};
	args.bracket = (t_bracket){0, 0};
	args.tokens = init_dynarray(2, (void *(*)(void *))destroy_token);
	return (args);
}
