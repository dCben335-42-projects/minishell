/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_shell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:05:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/29 18:04:37 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_SHELL_H
# define STRUCT_SHELL_H

# include "struct_env.h"
# include "struct_dynarray.h"
# include "ast_node.h"
# include <sys/types.h>

/**
 * @brief The debug structure.
 * 
 * @param all The debug mode for all.
 * @param tokens The debug mode only for tokens.
 * @param lexer The debug mode only for lexer.
 * @param ast The debug mode only for AST.
 * 
 * @note debug_all overrides all other debug modes.
 */
typedef struct s_debug
{
	t_bool   all;
	t_bool   tokens;
	t_bool   lexer;
	t_bool   ast;
	t_bool   exitcode;
}	t_debug;


/**
 * @brief The shell structure.
 * 
 * @param env The environment variables.
 * @param env_array The environment variables as a dynamic array.
 * @param current_path The current working directory.
 * @param exit_code The exit code of the last command.
 * @param last_pid The last process ID.
 * @param ast The abstract syntax tree.
 * @param debug The debug structure fot the custom debug builtin.
 * 
 * @note The env_array is meant to be pass to the execve function.
 * @note The last_pid is used especially when several processes are
 * created in the same time.
 */
typedef struct s_shell
{
	t_env		*env;
	t_dynarray  env_array;
	char		*current_path;
	int			exit_code;
	pid_t		last_pid;
	t_ast_node	*ast;
	t_bool		interrupted;
	t_debug		debug;
}	t_shell;

t_shell	init_shell(char **envp);
void	*destroy_shell(t_shell *shell);

#endif