/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:09:52 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/04 16:23:09 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.h"
#include "errors.h"

void	error_malloc(void *f(void *), void *data)
{
	perror(ERROR_MALLOC);
	if (f && data)
		f(data);
	exit(1);
}