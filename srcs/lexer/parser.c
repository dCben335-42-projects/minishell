#include "parser_lexer.h"

/**
 * Vérifie si un token est un opérateur de contrôle (&&, ||, |, ;, etc.)
 */
int is_control_operator(t_token_type type) {
    return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR ||
            type == TOKEN_SEMICOL || type == TOKEN_BACKGROUND ||
            type == TOKEN_PIPE_ERR);
}

/**
 * Vérifie la validité syntaxique d'une séquence de tokens
 */
int parse_tokens(t_token tokens[], int token_count) {
    if (token_count == 0) return 0;

    // Vérifier si la commande commence par un opérateur de contrôle interdit
    if (is_control_operator(tokens[0].type) && tokens[0].type != TOKEN_BACKGROUND) {
        fprintf(stderr, "Erreur de syntaxe : La commande ne peut pas commencer par '%s'\n", tokens[0].value);
        return 1;
    }

    for (int i = 0; i < token_count - 1; i++) {
        t_token_type current = tokens[i].type;
        t_token_type next = tokens[i + 1].type;

        // Vérifier si deux opérateurs de contrôle se suivent sans mot entre eux
        if (is_control_operator(current) && is_control_operator(next)) {
            fprintf(stderr, "Erreur de syntaxe : '%s' ne peut pas être suivi de '%s'\n", tokens[i].value, tokens[i + 1].value);
            return 1;
        }
    }

    // Vérifier si la commande se termine par un opérateur de contrôle (hors '&')
    if (is_control_operator(tokens[token_count - 2].type) && tokens[token_count - 2].type != TOKEN_BACKGROUND) {
        fprintf(stderr, "Erreur de syntaxe : La commande ne peut pas se terminer par '%s'\n", tokens[token_count - 2].value);
        return 1;
    }

    return 0;
}