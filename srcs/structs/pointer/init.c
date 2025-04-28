#include "struct_pointer.h"

t_pointer	init_pointer(void *pointer, t_bool is_malloc, t_bool has_malloc_error)
{
	t_pointer	new_pointer;

	new_pointer.pointer = pointer;
	new_pointer.is_malloc = is_malloc;
	new_pointer.has_malloc_error = has_malloc_error;
	return (new_pointer);
}

