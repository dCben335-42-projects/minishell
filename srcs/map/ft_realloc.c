#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction realloc personnalisée
void *ft_realloc(void *ptr, size_t size) {
    if (size == 0) { 
        free((size_t *)ptr - 1); // Libérer le vrai début du bloc
        return NULL;
    }

    if (!ptr) return malloc(size + sizeof(size_t)); // Nouvelle allocation
    
    // Récupérer la taille actuelle stockée avant le bloc
    size_t *old_size_ptr = (size_t *)ptr - 1;
    size_t old_size = *old_size_ptr;

    // Allouer un nouveau bloc avec l’espace pour stocker la nouvelle taille
    size_t *new_ptr = malloc(size + sizeof(size_t));
    if (!new_ptr) return NULL;

    // Copier les anciennes données (jusqu’à la plus petite taille)
    memcpy(new_ptr + 1, ptr, (old_size < size) ? old_size : size);

    free(old_size_ptr); // Libérer le bon pointeur (aligné sur malloc)

    // Stocker la nouvelle taille et retourner le pointeur utilisateur
    *new_ptr = size;
    return (void *)(new_ptr + 1);
}

// Fonction d'allocation qui stocke la taille
void *malloc_with_size(size_t size) {
    size_t *ptr = malloc(size + sizeof(size_t));
    if (!ptr) return NULL;
    *ptr = size; // Stocker la taille
    return (void *)(ptr + 1);
}

// Fonction de libération qui récupère le vrai pointeur
void free_malloc_size(void *ptr) {
    if (!ptr) return;
    free((size_t *)ptr - 1);
}

int main() {
    int *arr = malloc_with_size(3 * sizeof(int));
    arr[0] = 1; arr[1] = 2; arr[2] = 3;

    printf("Avant realloc: %d, %d, %d\n", arr[0], arr[1], arr[2]);

    arr = ft_realloc(arr, 5 * sizeof(int)); // Redimensionnement

    arr[3] = 4; arr[4] = 5;
    printf("Après realloc: %d, %d, %d, %d, %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);

    free_malloc_size(arr);
    return 0;
}
