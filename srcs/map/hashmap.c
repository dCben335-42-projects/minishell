#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 8   // Taille initiale
#define LOAD_FACTOR 0.75 // Facteur de charge max avant redimensionnement

// Structure d'un élément de la HashMap
typedef struct Entry {
    char *key;
    int value;
    struct Entry *next; // Gestion des collisions avec chaînage
} Entry;

// Structure de la HashMap
typedef struct {
    Entry **buckets;
    int size;
    int count;
} HashMap;

// Fonction de hachage simple (djb2)
unsigned int hash(const char *key, int size) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

// Création de la HashMap
HashMap *create_hashmap(int size) {
    HashMap *map = malloc(sizeof(HashMap));
    map->size = size;
    map->count = 0;
    map->buckets = calloc(size, sizeof(Entry *));
    return map;
}

// Insertion avec redimensionnement automatique
void insert(HashMap *map, const char *key, int value);

// Redimensionnement de la HashMap
void resize(HashMap *map) {
    int new_size = map->size * 2;
    Entry **new_buckets = calloc(new_size, sizeof(Entry *));
    
    for (int i = 0; i < map->size; i++) {
        Entry *entry = map->buckets[i];
        while (entry) {
            Entry *next = entry->next;
            unsigned int new_index = hash(entry->key, new_size);
            entry->next = new_buckets[new_index];
            new_buckets[new_index] = entry;
            entry = next;
        }
    }
    free(map->buckets);
    map->buckets = new_buckets;
    map->size = new_size;
}

// Fonction pour insérer une clé-valeur dans la HashMap
void insert(HashMap *map, const char *key, int value) {
    unsigned int index = hash(key, map->size);
    Entry *entry = map->buckets[index];
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }
    
    Entry *new_entry = malloc(sizeof(Entry));
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
    map->count++;
    
    if ((float)map->count / map->size > LOAD_FACTOR) {
        resize(map);
    }
}

// Recherche d'une clé
int get(HashMap *map, const char *key, int *found) {
    unsigned int index = hash(key, map->size);
    Entry *entry = map->buckets[index];
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            *found = 1;
            return entry->value;
        }
        entry = entry->next;
    }
    *found = 0;
    return 0;
}

// Fonction de libération de mémoire
void free_hashmap(HashMap *map) {
    for (int i = 0; i < map->size; i++) {
        Entry *entry = map->buckets[i];
        while (entry) {
            Entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}

// Programme principal
int main() {
    HashMap *map = create_hashmap(INITIAL_SIZE);
    insert(map, "Alice", 25);
    insert(map, "Bob", 30);
    insert(map, "Charlie", 35);
    
    int found;
    printf("Alice: %d\n", get(map, "Alice", &found));
    printf("Bob: %d\n", get(map, "Bob", &found));
    printf("Charlie: %d\n", get(map, "Charlie", &found));
    
    free_hashmap(map);
    return 0;
}
