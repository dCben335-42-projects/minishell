#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 100

// Définition des types de tokens
typedef enum e_token_type {
    TOKEN_WORD,        // Mot ou commande
    TOKEN_PIPE,        // |
    TOKEN_AND,         // &&
    TOKEN_OR,          // ||
    TOKEN_SEMICOL,     // ;
    TOKEN_REDIR_IN,    // <
    TOKEN_REDIR_OUT,   // >
    TOKEN_APPEND,      // >>
    TOKEN_BACKGROUND,  // &
    TOKEN_PIPE_ERR,    // |&
    TOKEN_EOF          // Fin de commande
} t_token_type;

typedef struct s_token_name {
    char *name;
} t_token_name;

// Structure d'un token
typedef struct s_token{
    t_token_type type;
    char value[MAX_TOKEN_LENGTH];
} token;

// Structure pour la table de transition des opérateurs
typedef struct {
    char next_char;
    t_token_type type;
} transition;

// Table des opérateurs spéciaux
typedef struct {
    char key;
    transition transitions[3]; // Max 3 transitions possibles par caractère
} operator_table;

operator_table op_table[] = {
    {   
        '|',
        {
            {'|', TOKEN_OR}, 
            {'&', TOKEN_PIPE_ERR}, 
            {'\0', TOKEN_PIPE}
        }
    },
    {
        '&',
        {
            {'&', TOKEN_AND}, 
            {'\0', TOKEN_BACKGROUND}
            }
        },
    {
        '>',
        {
            {'>', TOKEN_APPEND}, 
            {'\0', TOKEN_REDIR_OUT}
        }
    },
    {
        '<',
        {
            {'\0', TOKEN_REDIR_IN}
        }
    },
    {
        ';',
        {
            {'\0', TOKEN_SEMICOL}
            }
        }
};

t_token_name token_names[] = {
    {"WORD"},
    {"PIPE"},
    {"AND"},
    {"OR"},
    {"SEMICOL"},
    {"REDIR_IN"},
    {"REDIR_OUT"},
    {"APPEND"},
    {"BACKGROUND"},
    {"PIPE_ERR"},
    {"EOF"}
};

const int op_table_size = sizeof(op_table) / sizeof(op_table[0]);

// Fonction pour rechercher un opérateur dans la table
t_token_type find_operator(const char *input, int *offset) {
    for (int i = 0; i < op_table_size; i++) {
        if (op_table[i].key == input[0]) {
            for (int j = 0; j < 3; j++) {
                if (op_table[i].transitions[j].next_char == '\0' || op_table[i].transitions[j].next_char == input[1]) {
                    if (op_table[i].transitions[j].next_char != '\0') (*offset)++; // Avancer si double caractère
                    return op_table[i].transitions[j].type;
                }
            }
        }
    }
    return TOKEN_WORD; // Si ce n'est pas un opérateur, c'est un mot
}

// Fonction du lexer qui découpe la commande en tokens
void lexer(const char *input, token tokens[], int *token_count) {
    int i = 0, len = strlen(input);
    *token_count = 0;

    while (i < len) {
        if (isspace(input[i])) { i++; continue; }

        int offset = 0;
        t_token_type type = find_operator(&input[i], &offset);

        if (type != TOKEN_WORD) {
            // Ajout d'un opérateur trouvé
            tokens[*token_count].type = type;
            strncpy(tokens[*token_count].value, &input[i], offset + 1);
            tokens[*token_count].value[offset + 1] = '\0';
            (*token_count)++;
            i += (offset + 1);
        } else {
            // Gestion des mots (commandes, arguments, etc.)
            char buffer[MAX_TOKEN_LENGTH] = {0};
            int j = 0;
            while (i < len && !isspace(input[i]) && find_operator(&input[i], &offset) == TOKEN_WORD) {
                buffer[j++] = input[i++];
            }
            buffer[j] = '\0';
            tokens[*token_count].type = TOKEN_WORD;
            strncpy(tokens[*token_count].value, buffer, MAX_TOKEN_LENGTH - 1);
            (*token_count)++;
        }
    }

    // Ajouter un token EOF pour signaler la fin
    tokens[*token_count].type = TOKEN_EOF;
    strcpy(tokens[*token_count].value, "EOF");
    (*token_count)++;
}

// Fonction pour afficher les tokens
void print_tokens(token tokens[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Token: %-12s | Type: %s\n", tokens[i].value, token_names[tokens[i].type].name);
    }
}

// Programme principal (test)
int main() {
    //const char *command = "ls -l |& grep \"main.c\" && echo \"Done\" > output.txt";
    const char *command = "ls -l | grep \"main.c\" && echo \"Done\" > output.txt";
    token tokens[MAX_TOKENS];
    int token_count = 0;

    lexer(command, tokens, &token_count);
    print_tokens(tokens, token_count);

    return 0;
}
