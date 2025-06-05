/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 06:58:17 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 20:32:44 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"

/**
 * @brief Check if the token is a control token.
 *
 * @param token The token to check.
 * 
 * @note The function checks if the token type is a control token
 * by comparing it with the control masks.
 * 
 * @return 0 if the token is not a control token or a positive value
 * if it is a control token.
 */
int	is_control_token(t_token token)
{
	return (token.type & get_masks()->control);
}

/**
 * @brief Check if the token is a parenthesis token.
 *
 * @param token The token to check.
 * 
 * @note The function checks if the token type is a parenthesis token
 * by comparing it with the parenthesis masks.
 * 
 * @return 0 if the token is not a parenthesis token or a positive value
 * if it is a parenthesis token.
 */
int	is_parenthesis_token(t_token token)
{
	return (token.type & get_masks()->paren);
}

/**
 * @brief Check if the token is a control extended token.
 *
 * @param token The token to check.
 * 
 * @note The function checks if the token type is a control extended token
 * by comparing it with the control extended masks.
 * 
 * @return 0 if the token is not a control extended token or a positive value
 * if it is a control extended token.
 */
int	is_control_extended_token(t_token token)
{
	return (token.type & get_masks()->control_extended);
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
int	is_redir_token(t_token token)
{
	return (token.type & get_masks()->redir);
}
