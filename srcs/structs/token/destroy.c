/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:16:30 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 18:16:34 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"
#include <stdlib.h>

void	*destroy_token(t_token *token)
{
	free(token->value);
	free(token);
	return (NULL);
}
