#include "ast.h"

int count_new_cmd_child(int *i, int end, t_dynamic_array *tokens, t_bool *is_finished_by_space)
{
	t_token		*token;
	t_token		*last_token;
	int count;
	int start;

	last_token = NULL;
	start = *i;
	count = 0;
	token = (t_token *)get_value(tokens, start);
	*is_finished_by_space = FALSE;
	while (start < end && !is_operator_token(*token) && !is_parenthesis_token(*token))
	{
		if (token->type == TOKEN_SPACE && count == 0)
		{
			(*i)++;
		}
		else
		{
			last_token = token;
			count++;
		}
		start++;
		if (start < end)
			token = (t_token *)get_value(tokens, start);
	}
	if (last_token && last_token->type == TOKEN_SPACE)
	{
		*is_finished_by_space = TRUE;
		count--;
	}
	return (count);
}

t_ast_node	*get_cmd(t_dynamic_array *tokens, int *i, int end, t_bool *is_empty)
{
	t_ast_node	*new_cmd;
	t_token		*token;
	int count;
	t_bool		is_finished_by_space;

	*is_empty = FALSE;
	new_cmd = NULL;
	if (*i >= end)
		return (NULL);
	token = (t_token *)get_value(tokens, *i);
	if (is_text_token(*token) || is_redir_token(*token) || token->type == TOKEN_SPACE)
	{
		count = count_new_cmd_child(i, end, tokens, &is_finished_by_space);
		if (count > 0)
			new_cmd = init_node(CMD, NULL);
		else 
		{
			*is_empty = TRUE;
			return (NULL);
		}
		while (count--)
		{
			token = (t_token *)get_value(tokens, *i);
			add_child(new_cmd, convert_token_to_cmd(token));
			(*i)++;
		}
		if (is_finished_by_space)
			(*i)++;
	}
	else
	{
		(*i)++;
		return (convert_token_to_cmd(token));
	}
	return (new_cmd);
}
