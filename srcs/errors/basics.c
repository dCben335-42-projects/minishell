
#include "messages.h"
#include "errors.h"

void	error_malloc(void *f(void *), void *data)
{
	perror(ERROR_MALLOC);
	if (f && data)
		f(data);
	exit(1);
}