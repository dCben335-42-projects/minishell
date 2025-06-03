/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:09:41 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/03 16:28:32 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * 
 * @brief Negates the * and ? wildcards in the given token.
 * 
 * @param str A pointer to a string containing the token value.
 * 
 * @note This function iterates through the string and 
 * replaces * with -'*' and ? with -'?'.
 * 
*/
void	negate_wildcard(char **str)
{
	char *value;
	
	value = *str;
	while (*value)
	{
		if (*value == '*')
			*value = -'*';
		else if (*value == '?')
			*value = -'?';
		value++;
	}
}

void	positivate_wildcard(char **str)
{
	char *value;
	
	value = *str;
	while (*value)
	{
		if (*value == -'*')
			*value = '*';
		else if (*value == -'?')
			*value = '?';
		value++;
	}
}