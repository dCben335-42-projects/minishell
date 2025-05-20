#include "struct_pointer.h"

t_pointer	init_pointer(void *pointer, t_bool is_malloc)
{
	t_pointer	new_pointer;

	new_pointer.pointer = pointer;
	new_pointer.is_malloc = is_malloc;
	if (is_malloc && !pointer)
	{
		new_pointer.has_malloc_error = TRUE;
		return (new_pointer);
	}
	new_pointer.has_malloc_error = FALSE;
	return (new_pointer);
}

