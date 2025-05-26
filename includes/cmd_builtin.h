/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:10:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/26 15:40:26 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_BUILTIN_H
# define CMD_BUILTIN_H

# include "struct_shell.h"

t_bool	is_builtin(t_shell *shell, t_dynarray *cmd, char **args);

/**
 * @brief The builtin structure.
 * 
 * @param name The name of the builtin command.
 * @param f The function pointer to the builtin command to be 
 * called when the first argument is the name of the builtin command.
 * 
 * @note The function pointer is used to call the builtin command.
 */
typedef struct s_builtin
{
	char	*name;
	void	(*f)(t_shell *shell, char **args);
}	t_builtin;

# define BUILTIN_ENV "env"
# define BUILTIN_CD "cd"
# define BUILTIN_EXPORT "export"
# define BUILTIN_UNSET "unset"
# define BUILTIN_PWD "pwd"
# define BUILTIN_EXIT "exit"
# define BUILTIN_ECHO "echo"
# define BUILTIN_DEBUG "debug"

void	ft_env(t_shell *shell, char **args);
void	ft_export(t_shell *shell, char **args);
void	ft_unset(t_shell *shell, char **args);
void	ft_pwd(t_shell *shell, char **args);
void	ft_cd(t_shell *shell, char **args);
void	ft_exit(t_shell *shell, char **args);
void	ft_echo(t_shell *shell, char **args);
void	ft_debug(t_shell *shell, char **args);

# define DEBUG_ALL_OPTION "--all"
# define DEBUG_TOKENS_OPTION "--tokens"
# define DEBUG_AST_OPTION "--ast"
# define DEBUG_EXITCODE_OPTION "--exitcode"
# define DEBUG_HELP_OPTION "--help"

# define DEBUG_HELP_MSG "Try debug --help for more information.\n"
# define DEBUG_OPTIONS_MSG \
"All debug options:\n\
\t--help\t\tShow this help message\n \
\t--all\t\tToggle debug mode which if activated will override all other debug modes\n \
\t--tokens\tToggle debug mode for tokens gotten from lexer\n \
\t--ast\t\tToggle debug mode for AST\n \
\t--exitcode\tShow the exit code of the last command\n"

/**
 * @brief The debug structure.
 * 
 * @param options The string options for the debug mode.
 * @param toggle The boolean to toggle when the option is encountered.
 *
 * @note The options are used to identify the debug mode to be toggled.
*/
typedef struct s_debug_map
{
	const char	*option;
	t_bool		*toggle;
}	t_debug_map;

#endif