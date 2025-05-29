/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:18:20 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/29 16:26:24 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_lexer_args.h"

void	*destroy_lexer_args(t_lexer_args *args, t_bool destroy_heredocs)
{
	destroy_dynarray(&args->tokens);
	if (destroy_heredocs)
		destroy_dynarray(args->heredoc_cval);
	return (NULL);
}
