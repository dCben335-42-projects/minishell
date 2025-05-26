#include "struct_token.h"
#include "struct_lexer_args.h"
#include "messages.h"

static const t_readline_state *get_readline_map(void)
{
	static const t_readline_state	map[] = {
	{OP_AND, READLINE_AND_VAL},
	{OP_OR, READLINE_OR_VAL},
	{OP_PIPE, READLINE_PIPE_VAL},
	{R_HEREDOC, READLINE_HEREDOC_VAL},
	{R_HEREDOC_TRIM, READLINE_HEREDOC_TRIM_VAL},
	{READLINE_D_QUOTE_KEY, READLINE_D_QUOTE_VAL},
	{READLINE_S_QUOTE_KEY, READLINE_S_QUOTE_VAL},
	{0, READLINE_PARENTHESIS_VAL}};

	return (map);
}

const char *get_readline_arg(t_token_type type)
{
	const t_readline_state	*map = get_readline_map();

	while (map->type)
	{
		if (map->type == type)
			return (map->value);
		map++;
	}
	return (map->value);
}