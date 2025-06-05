#include "parsing.h"
#include "ast.h"
#include "minishell.h"
#include "fcntl.h"

static t_bool	is_command_finished(t_lexer_args *args, t_token *token, const char *input)
{
	if (!args->check_rules)
		return (TRUE);
	if (token->rules & EXPECT_CONT || args->parenthesis.open > args->parenthesis.close)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
		{
			args->not_finished_value = get_readline_arg(token->type);
			return (FALSE);
		}
	}
	return (TRUE);
}

static t_ptr	get_next_token(t_lexer_args *args)
{
	if (!*args->input)
		return (init_pointer(NULL, FALSE));
	if (args->quote == DELIMITER_EXPANDABLE_TEXT 
		&& *args->input == DELIMITER_EXPANDABLE_TEXT)
	{
		args->input++;
		args->quote = 0;
	}
	if (ft_isspace(*args->input) && args->quote == 0)
		return (tokenize_whitespace(args));
	if (!*args->input)
		return (init_pointer(NULL, FALSE));
	return (get_token(args));
}

t_parse_status	get_parsing_error_status(t_lexer_args *args, t_ptr ptr)
{
    t_parse_status  status;

	if (ptr.has_malloc_error)
		return (MALLOC_ERROR);
    status = token_parser(args, ptr.p);
    if (status != COMMAND_VALID)
		return (status);
    if (!is_command_finished(args, ptr.p, args->input))
		return (COMMAND_NOT_FINISHED);
    return (status);
}


int is_heredoc_token(t_token *token);
int is_text_tokenn(t_token *token);
int is_meta_tokenn(t_token *token);

int is_meta_tokenn(t_token *token)
{
	return (token->type & get_masks()->metachar);
}

#include "utils.h"

int is_quoted_text_token(t_token *token)
{
	return (token->type & (QUOTED_TEXT | QUOTED_EXPAND));
}

t_ptr handle_heredoc(t_lexer_args *args, t_token *token)
{
	t_ptr		ptr;
	t_ptr		next_ptr;
	t_bool		is_expandable_heredoc;
	char		*delimer;
	char		*tmp;

	ptr = get_next_token(args);
	delimer = ft_strdup("");
	is_expandable_heredoc = FALSE;
	if (ptr.p && is_meta_tokenn(ptr.p))
	{
		destroy_token(ptr.p);
		ptr = get_next_token(args);
	}
	if (!ptr.p || !is_text_tokenn(ptr.p))
		return (ptr);
	while (ptr.p && is_text_tokenn(ptr.p))
	{
		if (is_quoted_text_token(ptr.p))
			is_expandable_heredoc = TRUE;
		tmp = ft_strjoin(delimer, ((t_token *)(ptr.p))->value);
		free(delimer);
		delimer = tmp;
		next_ptr = get_next_token(args);
		if (!next_ptr.p || !is_text_tokenn(next_ptr.p))
		{
			get_parsing_error_status(args, ptr);
			break;
		}
		destroy_token(ptr.p);
		ptr = next_ptr;
	}
	free(((t_token *)(ptr.p))->value);
	((t_token *)(ptr.p))->value = delimer;
	get_parsing_error_status(args, transform_heredoc(args, ptr.p, is_expandable_heredoc, token->type));
	return (next_ptr);
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
    t_ptr		ptr;
    t_parse_status	status;

    ptr = get_next_token(args);
    while (ptr.p)
	{
		status = get_parsing_error_status(args, ptr);
        if (status != COMMAND_VALID)
            return (status);
        if (args->is_heredoc)
			ptr = handle_heredoc(args, ptr.p);
		else
			ptr = get_next_token(args);
    }
	if (ptr.has_malloc_error)
		return (MALLOC_ERROR);
    ptr = init_pointer(init_token(M_EOF, "newline", 7), TRUE);
    if (ptr.has_malloc_error)
		return (MALLOC_ERROR);
    return (token_parser(args, ptr.p));
}


//( ( ( echo jojo$PATH'$GOOD'"okksa   'fjeifj'          iji*ji$HELLO"jigo/*'ffe'./?out) )&& echo $'bonjour'"salut $" ); >>test

// bash: erreur de syntaxe : fin de fichier prématurée