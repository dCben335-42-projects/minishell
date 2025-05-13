#include "ast.h"
#include "struct_dynarray.h"
#include "struct_shell.h"

typedef struct s_exec_map
{
	t_node_type	type;
	void		(*f)(t_shell *shell, t_dynarray *cmd);
}	t_exec_map;

static const t_exec_map	*get_exec_map(void)
{
	static const t_exec_map	map[] = {
	{CMD_SEQ, NULL},
	{CMD_JOIN, NULL},
	{CMD_AND, NULL},
	{CMD_OR, NULL},
	{CMD_PIPE, NULL},
	{CMD_PARENTHESIS, NULL},
	{0, NULL}};

	return (map);
}

static t_bool is_mp(const t_node_type type)
{
	const t_exec_map	*map = get_exec_map();

	while (map->type)
	{
		if (map->type == type)
			return (TRUE);
		map++;
	}
	return (FALSE);
}

t_ast_node *skip_cmd(t_ast_node *node)
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

t_ast_node *find_next_cmd(t_ast_node *prev_node)
{
	t_ast_node	*child;
	if (prev_node == NULL)
		return (NULL);
	child = get_dynarray_value(prev_node->content, 0);
	if (child && is_mp(child->type))
		return (child);
	return (skip_cmd(prev_node));
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