#include "parsing.h"
#include "ast.h"
#include "minishell.h"
#include "fcntl.h"

static t_bool	is_command_finished(const char *input, t_token *token, t_lexer_args *args)
{
	if (token->rules & EXPECT_CONT || args->parenthesis.open > args->parenthesis.close)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			return (FALSE);
	}
	return (TRUE);
}

static t_ptr	get_next_token(t_lexer_args *args)
{
    int offset;

    while (*args->input)
    {
        if (args->quote == DELIMITER_EXPANDABLE_TEXT 
			&& *args->input == DELIMITER_EXPANDABLE_TEXT)
        {
            args->input++;
            args->quote = 0;
            continue ;
        }
        if (ft_isspace(*args->input) && args->quote == 0)
            return (tokenize_whitespace(args));
        offset = 0;
        return (get_token(args, offset, get_token_type(args->input, &offset)));
    }
	return (init_pointer(NULL, FALSE));
}

t_parse_status	get_parsing_error_status(t_lexer_args *args, t_ptr pointer)
{
    t_parse_status  status;

	if (pointer.has_malloc_error)
		return (MALLOC_ERROR);
    status = token_parser(args, pointer.p);
    if (status != COMMAND_VALID)
		return (status);
    if (!is_command_finished(args->input, pointer.p, args))
		return (COMMAND_NOT_FINISHED);
    return (status);
}
/**
 * @brief Analyzes the input to determine if it follows a valid command format.
 *
 * This function processes the input string using lexical analysis 
 * to extract tokens and validate the command structure.
 *
 * @param args The lexer arguments containing the input string and 
 * parsing context.
 * @return The status of the command parsing:
 * - `COMMAND_VALID` if the command is correctly formatted.
 * - `COMMAND_NOT_VALID` if the command contains syntax errors.
 * - `COMMAND_NOT_FINISHED` if the command is incomplete
 * (e.g., missing closing quotes).
 */
t_parse_status    lexer(t_lexer_args *args)
{
    t_ptr		pointer;
    t_parse_status	status;

    pointer = get_next_token(args);
    while (pointer.p)
	{
		status = get_parsing_error_status(args, pointer);
        if (status != COMMAND_VALID)
            return (status);
        if (args->is_heredoc && is_text_token(*((t_token *)pointer.p)))
           	pointer = transform_heredoc(args, pointer.p);
		else
			pointer = get_next_token(args);
    }
	if (pointer.has_malloc_error)
		return (MALLOC_ERROR);
    pointer = init_pointer(init_token(M_EOF, "newline", 7), TRUE);
    if (!(pointer.p))
        return (MALLOC_ERROR);
    return (token_parser(args, pointer.p));
}


// ( ( ( echo jojo$PATH'$GOOD'"okksa   'fjeifj'          iji*ji$HELLO"jigo/*'ffe'./?out) )&& echo $'bonjour'"salut $" )
// bash: erreur de syntaxe : fin de fichier prématurée