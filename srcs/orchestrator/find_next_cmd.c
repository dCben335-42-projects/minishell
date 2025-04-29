#include "ast.h"

t_ast_node *get_next_cmd(t_ast_node *node)
{
	t_ast_node *next_node;

	next_node = node;
	while (!next_node->next)
	{
		if (next_node->parent == NULL)
			return (NULL);
		next_node = next_node->parent;
	}
	return (next_node->next);
}

t_ast_node *find_next_cmd_recursive(t_bool is_start, t_ast_node *node)
{
	if (node == NULL)
		return (NULL);
	if (is_start)
		return (find_next_cmd_recursive(FALSE, get_next_cmd(node)));
	if (node->type == CMD_JOIN)
		return (node);
	else
		return (find_next_cmd_recursive(FALSE, (t_ast_node *)get_dynarray_value(node->content, 0)));
}

t_ast_node *find_next_cmd(t_ast_node *master_node)
{
	static t_ast_node	*last_node = NULL;

	if (last_node)
		last_node = find_next_cmd_recursive(TRUE, last_node);
	else
	{
		last_node = master_node;
		last_node = find_next_cmd_recursive(FALSE, last_node);
	}
	return (last_node);
}








// ( ( ( echo 'salut' ) ) && echo 'bonjour' ) | echo bar | echo "sa va"



/*
Si node == CMD return TABLEAU DE CMD + CONTEXT
*/
































//int	planner(t_dynamic_array *cmds)
//{
//	int	i;
//	t_ast_node *node;

//	i = 0;
//	while (i < cmds->count)
//	{
//		node = (t_ast_node *)get_value(cmds, i);
//		if (node->type == CMD_PIPE)
//		{
//			excecute_cmd_pipe(node->content);
//		}
//	}

//}