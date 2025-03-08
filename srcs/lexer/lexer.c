#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 100
#define OP_TABLE_SIZE 5
#define OP_TABLE_MAX_BRANCH 3

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

typedef struct s_token{
    t_token_type type;
    char value[MAX_TOKEN_LENGTH];
} token;

typedef struct {
    char next_char;
    t_token_type type;
} transition;

typedef struct {
    char key;
    transition transitions[OP_TABLE_MAX_BRANCH];
} operator_table;

operator_table op_table[OP_TABLE_SIZE] = {
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

/**
 * Fonction pour trouver le type de token
 * @param input: chaîne d'entrée
 * @param offset: décalage pour le prochain caractère
 */

t_token_type find_token_type(const char *input, int *offset)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < OP_TABLE_SIZE)
    {
        if (op_table[i].key == input[0])
        {
            while (j < OP_TABLE_MAX_BRANCH)
            {
                if (op_table[i].transitions[j].next_char == '\0' || op_table[i].transitions[j].next_char == input[1])
                {
                    if (op_table[i].transitions[j].next_char != '\0') 
                        (*offset)++;
                    return op_table[i].transitions[j].type;
                }
                j++;
            }
        }
        i++;
    }
    return (TOKEN_WORD);
}

/**
 * Fonction pour analyser la chaîne d'entrée et générer des tokens
 * @param input: chaîne d'entrée
 * @param tokens: tableau de tokens
 * @param token_count: nombre de tokens
 */

void lexer(const char *input, token tokens[], int *token_count)
{
    int i = 0, len = strlen(input);
    *token_count = 0;

    while (i < len)
    {
        if (isspace(input[i]))
        { 
            i++; 
            continue; 
        }

        int offset = 0;
        t_token_type type = find_token_type(&input[i], &offset);

        if (type != TOKEN_WORD)
        {
            tokens[*token_count].type = type;
            strncpy(tokens[*token_count].value, &input[i], offset + 1);
            tokens[*token_count].value[offset + 1] = '\0';
            (*token_count)++;
            i += (offset + 1);
        }
        else
        {
            char buffer[MAX_TOKEN_LENGTH] = {0};
            int j = 0;
            while (i < len && !isspace(input[i]) && find_token_type(&input[i], &offset) == TOKEN_WORD) {
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

/**
 * Fonction pour afficher les tokens
 * @param tokens: tableau de tokens
 * @param count: nombre de tokens
 */

void print_tokens(token tokens[], int count)
{
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
