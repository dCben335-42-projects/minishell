/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:18:20 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 18:18:21 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_lexer_args.h"

void	*destroy_lexer_args(t_lexer_args *args)
{
	destroy_dynarray(&args->tokens);
	free(args->error);
	free((char *)args->input);
	return (NULL);
}
