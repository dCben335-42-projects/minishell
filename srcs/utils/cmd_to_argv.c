

#include "libft_tree.h"
#include "libft.h"
#include "struct_dynarray.h"
#include "stdio.h"
#include "cmd_expand.h"
#include "struct_shell.h"

static void	cleanup_args(t_dynarray *arr)
{
	t_uint	i;
	t_uint	j;
	t_uint	count;
	char	*str;
	
	if (!arr || !arr->data)
		return;
	i = 0;
	j = 0;
	count = arr->count;
	while (i < count)
	{
		str = get_dynarray_value(arr, i);
		if (str && *str)
			arr->data[j++] = arr->data[i];
		else if (arr->destroyer)
			arr->destroyer(arr->data[i]); 
		i++;
	}
	arr->count = j;
	while (j < count)
		arr->data[j++] = NULL;
}

static void	*push_tree_values(t_tree *tree, t_dynarray *arr)
{
	char *value;
	if (!tree || !arr)
		return (NULL);
	push_tree_values(tree->left, arr);
	value = ft_strdup(tree->value);
	if (!value || !push(arr, value))
		return (NULL);
	push_tree_values(tree->right, arr);
	return (arr);
}

static char *save_word(t_shell *shell, t_dynarray *argv, t_dynarray *word)
{
	t_tree	*tree;

	tree = expand_word(shell, word);
	if (!tree)	
		return (NULL);
	if (!push_tree_values(tree, argv))
		return (destroy_tree(tree));
	destroy_tree(tree);
	return (argv->data[argv->count - 1]);
}

static void	skip_redirection(t_uint *i, t_uint count, t_dynarray *arr)
{
	t_ast_node	*node;

	while (*i < count)
	{
		node = (t_ast_node *)get_dynarray_value(arr, *i);
		if (node->type == CMD_WORD)
			break ;
		(*i)++;
	}
}

t_dynarray	*cmd_to_argv(t_shell *shell, t_dynarray *arr, t_dynarray *argv)
{
	t_ast_node	*node;
	t_uint		i;

	if (!argv->data)
		return (NULL);
	i = 0;
	while (i < arr->count)
	{
		skip_redirection(&i, arr->count, arr);
		node = (t_ast_node *)get_dynarray_value(arr, i);
		if (node && !save_word(shell, argv, node->content))
			return (destroy_dynarray(argv));
		i++;
	}
	cleanup_args(argv);
	return (argv);
}