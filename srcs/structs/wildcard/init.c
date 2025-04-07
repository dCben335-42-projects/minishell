/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:51:44 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/07 18:54:02 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"

t_wildcard	init_wildcard(const char *str)
{
	t_wildcard	wildcard;
	
	wildcard.is_error = FALSE;
	wildcard.pattern = NULL;
	wildcard.prefix = NULL;
	wildcard.suffix = NULL;
	wildcard.path = NULL;
	wildcard.arr = init_dynarray(1, &basic_destroyer);
	wildcard.is_prefix = is_prefix(str, &wildcard.prefix);
	wildcard.is_suffix = is_suffix(str, &wildcard.suffix);
	if ((wildcard.is_prefix && !wildcard.prefix) ||
		(wildcard.is_suffix && !wildcard.suffix))
	{
		destroy_wildcard(&wildcard);
		return (wildcard);
	}
	wildcard.pattern = get_wildcard_pattern(str, wildcard.prefix, wildcard.suffix);
	if (!wildcard.pattern)
	{
		destroy_wildcard(&wildcard);
		return (wildcard);
	}
	return (wildcard);
}