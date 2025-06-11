/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:39:44 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 03:16:12 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <stdio.h>

// SECTION: SHELL CONFIG

// ANCHOR - SHELL NAME
# define SHELL_NAME "SHELLOSTS"

// ANCHOR - FEATURE FLAG
# define FLAG_WILDCARD_EXPANSION	TRUE
# define FLAG_VAR_EXPANSION			TRUE
# define FLAG_ATTY_ONLY				TRUE
# define FLAG_BANNER				TRUE

# define FLAG_BUILTIN_CD			TRUE
# define FLAG_BUILTIN_ECHO			TRUE
# define FLAG_BUILTIN_ENV			TRUE
# define FLAG_BUILTIN_EXPORT		TRUE
# define FLAG_BUILTIN_PWD			TRUE
# define FLAG_BUILTIN_EXIT			TRUE
# define FLAG_BUILTIN_UNSET			TRUE
# define FLAG_BUILTIN_DEBUG			FALSE
# define FLAG_BUILTIN_VOID			FALSE

# define FLAG_LOGICAL_NEGATION		FALSE

// ANCHOR - ENVIRONMENT VARIABLES
# define FLAG_SET_DEFAULT_ENV		TRUE
# define FLAG_UPDATE_SHLVL			TRUE
# define DEFAULT_PATH				"/bin:/usr/bin:/usr/local/bin"

// ANCHOR - READLINE PROMPT
# define READLINE_S_QUOTE_VAL 		"single_quote>"
# define READLINE_D_QUOTE_VAL 		"double_quote>"
# define READLINE_PARENTHESIS_VAL 	"subshell>"
# define READLINE_HEREDOC_VAL 		"heredoc>"
# define READLINE_HEREDOC_TRIM_VAL 	"dash_heredoc>"
# define READLINE_AND_VAL			"and>"
# define READLINE_OR_VAL			"or>"
# define READLINE_PIPE_VAL			"pipe>"
# define READLINE_HEREDOC_VAL		"heredoc>"
# define READLINE_HEREDOC_TRIM_VAL	"dash_heredoc>"

// !SECTION
// SECTION: LEXER CONFIG

// ANCHOR - EXPANDABLES
# define SYMBOL_VAR_EXPAND			'$'

// ANCHOR - WILDCARDS
# define SYMBOL_GLOB_ANY			'*'
# define SYMBOL_GLOB_ONE			'?'

// ANCHOR - WORD
# define SYMBOL_QUOTE_LITERAL 		'\''
# define SYMBOL_QUOTE_EXPAND		'\"'

// !SECTION
// SECTION: COLORS

# define ESC_START "\001"
# define ESC_END   "\002"

# define FIRST_COL     "\033[1;35m"
# define SECOND_COL    "\033[1;34m"
# define VARIANT_COL   "\033[1;36m"
# define ACCENT_COL    "\033[1;32m"
# define COMMAND_COL   "\033[33m"
# define RESET_COL     "\033[0m"

# define FIRST_COL_RL     "\001\033[1;35m\002"
# define SECOND_COL_RL    "\001\033[1;34m\002"
# define VARIANT_COL_RL   "\001\033[1;36m\002"
# define ACCENT_COL_RL    "\001\033[1;32m\002"
# define COMMAND_COL_RL   "\001\033[33m\002"
# define RESET_COL_RL     "\001\033[0m\002"

# define KEY_COL FIRST_COL
# define VALUE_COL SECOND_COL
# define BRACE_COL VARIANT_COL

// !SECTION
// SECTION: MESSAGES

# define ERR_ATTY_ONLY \
"Error: Shellost only works in an interactive terminal."

# define ERR_SIGQUIT "Quit (core dumped)"

# define ERR_IS_DERECTORY "Is a directory"
# define ERR_NOT_FOUND "Command not found"

# define ERR_SYNTAX_EOF "Syntax error: unexpected end of file"

# define ERROR_MALLOC "Error: malloc"

# define ERR_CD "cd"
# define ERR_CD_HOME "cd: HOME not set"
# define ERR_CD_OLDPWD "cd: OLDPWD not set"
# define ERR_CD_ARGS "cd: too many arguments"

# define ERR_GETCWD \
"chdir: error retrieving current directory: \
getcwd: cannot access parent directories"

# define ERR_PWD \
"shellost: pwd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory"

# define ERROR_SHELL_INIT \
"shellost-init: error retrieving current directory: \
getcwd: cannot access parent directories"

# define EXIT_MSG "exit"
# define ERROR_EXIT_ARGS_NUM "exit: too many arguments"
# define ERROR_EXIT_NUM "exit: numeric argument required"

# define EXPORT_PREFIX "export"
# define ERR_EXPORT_ID "export: '%s': not a valid identifier\n"

# define SYNTAX_ERR_START "syntax error near unexpected token `"
# define SYNTAX_ERR_END "'\n"

// !SECTION

#endif