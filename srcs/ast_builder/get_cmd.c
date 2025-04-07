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

t_ast_node	*get_cmd(t_get_cmd_master args, int *i, t_bool *is_empty)
{
	t_ast_node	*new_cmd;
	t_token		*token;
	int count;
	t_bool		is_finished_by_space;
	t_ast_node	*temp_cmd;

	*is_empty = FALSE;
	new_cmd = NULL;
	if (*i >= args.end)
		return (NULL);
	token = (t_token *)get_value(args.tokens, *i);
	if (is_text_token(*token) || is_redir_token(*token) || token->type == TOKEN_SPACE)
	{
		count = count_new_cmd_child(i, args.end, args.tokens, &is_finished_by_space);
		if (count > 0)
			new_cmd = init_node_secure(CMD, NULL, args);
		else 
		{
			*is_empty = TRUE;
			return (NULL);
		}
		while (count--)
		{
			token = (t_token *)get_value(args.tokens, *i);
			temp_cmd = convert_token_to_cmd_secure(token, args);
			add_child_secure(new_cmd, &temp_cmd, args);
			(*i)++;
		}
		if (is_finished_by_space)
			(*i)++;
	}
	else
	{
		(*i)++;
		return (convert_token_to_cmd_secure(token, args));
	}
	return (new_cmd);
}
