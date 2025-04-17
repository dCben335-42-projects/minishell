/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:51:41 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/17 20:10:17 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"

t_bool	is_valid_wildcard(t_wildcard *wildcard)
{
	if (!wildcard)
		return (FALSE);
	if (wildcard->is_prefix && !wildcard->prefix)
		return (FALSE);
	if (wildcard->is_suffix && !wildcard->suffix)
		return (FALSE);
	if (!wildcard->base_path)
		return (FALSE);
	if (!wildcard->pattern)
		return (FALSE);
	return (TRUE);
}
