#include "token.h"
#include <stdlib.h>

void	*destroy_token(t_token *token)
{
	free(token->value);	
	free(token);
	return (NULL);
}