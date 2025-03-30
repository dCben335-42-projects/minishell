#include "ast.h"

t_ast_node	*get_cmd(t_dynamic_array *tokens, int *i, int end)
{
	t_ast_node	*new_cmd;
	t_token		*token;

	new_cmd = NULL;
	if (*i >= end)
		return (NULL);
	token = (t_token *)get_value(tokens, *i);
	if (is_text_token(*token))
	{
		while (*i < end && !is_operator_token(*token))
		{
			if (!new_cmd)
				new_cmd = init_node(CMD, NULL);
			add_child(new_cmd, convert_token_to_cmd(token));
			(*i)++;
			if (*i < end)
				token = (t_token *)get_value(tokens, *i);
		}
	}
	else
	{
		(*i)++;
		return (convert_token_to_cmd(token));
	}
	return (new_cmd);
}
