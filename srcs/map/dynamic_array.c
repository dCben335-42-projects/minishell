#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "types.h"
#include "libft.h"
#include "parser_lexer.h"

t_dynamic_array	*create_dynamic_array(t_uint size)
{
	t_dynamic_array	*arr;

	arr = malloc(sizeof(t_dynamic_array));
	arr->data = ft_calloc(size, sizeof(void *));
	arr->size = size;
	return (arr);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}

void	set_value(t_dynamic_array *arr, t_uint index, void *value)
{
	unsigned int	new_size;
	size_t			i;

	if (index >= arr->size)
	{
		new_size = arr->size * 2;
		arr->data = ft_realloc(arr->data, arr->size * sizeof(void *),
				new_size * sizeof(void *));
		i = arr->size;
		while (i < new_size)
		{
			arr->data[i] = 0;
			i++;
		}
		arr->size = new_size;
	}
	arr->data[index] = value;
}

void	*get_value(t_dynamic_array *arr, t_uint index)
{
	if (index < arr->size)
		return (arr->data[index]);
	return (0);
}

void	free_dynamic_array(t_dynamic_array *arr, void (*free_func)(void *))
{
	size_t i;

	i = 0;
	if (free_func != NULL)
	{
		while (i < arr->size)
		{
			if (arr->data[i] != NULL) {
				free_func(arr->data[i]);
				//free(arr->data[i]);
			}
			i++;
		}
	}
	free(arr->data);
	free(arr);
}

//void free_token(void *token)
//{
//	t_token *tok = (t_token *)token;
//	if (tok->value != NULL) {
//		free(tok->value);
//		tok->value = NULL;
//	}
//}

//int main() {
//    t_dynamic_array *arr = create_dynamic_array(2);

//    // Ajouter un entier
//	t_token val1 = (t_token){TOKEN_LITERAL_TEXT, ft_strdup("bonjour")};
//    set_value(arr, 0, &val1);

//	t_token val2 = (t_token){TOKEN_LITERAL_TEXT, ft_strdup("bonjour2")};
//    set_value(arr, 1, &val2);

//    printf("arr[0] = %s\n", ((t_token *)get_value(arr, 0))->value);
//    printf("arr[1] = %s\n", ((t_token *)get_value(arr, 1))->value);
//    // Libérer la mémoire
//    free_dynamic_array(arr, free_token);

//    return 0;
//}








//void free_array(t_dynamic_array *arr)
//{
//    // Libérer chaque élément du tableau dynamique s'il est alloué dynamiquement
//    for (int i = 0; i < arr->size; i++) {
//        if (arr->data[i] != NULL) {
//            free(arr->data[i]);  // Libère la mémoire allouée pour chaque élément
//        }
//    }

//    free(arr->data);  // Libère la mémoire allouée pour le tableau dynamique lui-même
//    free(arr);         // Libère la structure qui contient le tableau dynamique
//}


//int main(void)
//{
//	t_dynamic_array *arr;
//	int value1 = 42;
//	char *value2 = "Hello, world!";
//	char *value3 = "BONJOUR!";

//	arr = create_dynamic_array(4);
//	set_value(arr, 2, &value1);  // Stocke un int
//	set_value(arr, 10, value2);   // Stocke un char* (string)
//	set_value(arr, 10, value3);   // Stocke un char* (string)
	
//	printf("arr[2] = %d\n", *(int *)get_value(arr, 2));  // Cast pour récupérer l'int
//	printf("arr[10] = %s\n", (char *)get_value(arr, 10));  // Cast pour récupérer la string
	
//	// Tester un index qui n'a pas encore de valeur assignée
//	if (get_value(arr, 5) == NULL)
//	{
//		printf("arr[5] is NULL\n");
//	}

//	free_array(arr);
//	return (0);
//}

//int main(void) {
//    t_dynamic_array *arr = create_dynamic_array(4);

//    // Ajouter des entiers au tableau
//    for (int i = 0; i < 10; i++) {
//        int *value = malloc(sizeof(int));
//        if (!value) {
//            perror("Échec de l'allocation de mémoire pour la valeur");
//            free_array(arr, TRUE);
//            exit(EXIT_FAILURE);
//        }
//        *value = i * i; // Stocker le carré de l'indice
//        set_value(arr, i, value);
//    }

//    // Afficher les valeurs du tableau
//    for (int i = 0; i < 10; i++) {
//        int *value = get_value(arr, i);
//        if (value != NULL) {
//            printf("arr[%d] = %d\n", i, *value);
//        }
//    }

//    // Libérer la mémoire allouée
//    free_array(arr, TRUE);

//    return 0;
//}

