/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:18:20 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/29 13:52:48 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_lexer_args.h"

void	*destroy_lexer_args(t_lexer_args *args)
{
	destroy_dynarray(&args->tokens);
	free(args->error);
	return (NULL);
}
