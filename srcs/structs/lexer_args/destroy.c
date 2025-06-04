/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:18:20 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 18:22:45 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_lexer_args.h"

/**
 * 
 * @brief Destroys the lexer arguments structure and its contents.
 * 
 * @param args The lexer arguments structure to be destroyed.
 * @param destroy_heredocs A boolean indicating whether to destroy
 * the cached heredocs.
 * 
 * @return NULL
 * 
*/
void	*destroy_lexer_args(t_lexer_args *args, t_bool destroy_heredocs)
{
	destroy_dynarray(&args->tokens);
	if (destroy_heredocs)
		destroy_dynarray(args->heredoc_cval);
	return (NULL);
}
