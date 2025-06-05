/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:16:30 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 20:47:05 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"
#include <stdlib.h>

/**
 * @brief Destroys a token structure.
 *
 * @param token The token structure to destroy.
 * 
 * @return NULL
 * 
 * @note This function frees the memory allocated for the token structure
 * and its value. It returns NULL to indicate that the token has been destroyed.
 */
void	*destroy_token(t_token *token)
{
	free(token->value);
	free(token);
	return (NULL);
}
