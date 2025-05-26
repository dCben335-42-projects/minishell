/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 06:59:55 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 08:00:44 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"

/**
 * @brief Check if the token is a command token.
 *
 * @param token The token to check.
 * 
 * @note The function checks if the token type is a command token
 * by comparing it with the command masks.
 * 
 * @return 0 if the token is not a command token or a positive value
 * if it is a command token.
*/
int is_cmd_token(t_token token)
{
	return (token.type & (get_masks()->redir | get_masks()->text | M_SPACE));
}

/**
 * @brief Check if the token is a text token.
 *
 * @param token The token to check.
 * 
 * @note The function checks if the token type is a text token
 * by comparing it with the text masks.
 * 
 * @return 0 if the token is not a text token or a positive value
 * if it is a text token.
 */
int	is_text_token(t_token token)
{
	return (token.type & get_masks()->text);
}

/**
 * @brief Check if the token is a redirection token.
 *
 * @param token The token to check.
 * 
 * @note The function checks if the token type is a redirection token
 * by comparing it with the redirection masks.
 * 
 * @return 0 if the token is not a redirection token or a positive value
 * if it is a redirection token.
 */
int	is_meta_token(t_token token)
{
	return (token.type & get_masks()->metachar);
}