#include "parser_lexer.h"


//int error_handler(t_token tokens[], int i)
//{
//    fprintf(stderr, "erreur de syntaxe près du symbole inattendu « %s »\n", tokens[i].value, tokens[i + 1].value);

//    return (1);
//}

size_t	ft_strcat(char *dest, const char *src)
{
    size_t	i;
    size_t	j;

    i = 0;
    j = 0;
    while (dest[i])
        i++;
    while (src[j])
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return (i);
}



/**
 * Vérifie si un token est un opérateur de contrôle (&&, ||, |, ;, etc.)
 */
int is_control_operator(t_token_type type) {
    return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR ||
            type == TOKEN_SEMICOL || type == TOKEN_BACKGROUND ||
            type == TOKEN_PIPE_ERR || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT);
}

/**
 * Vérifie la validité syntaxique d'une séquence de tokens
 */
int parse_tokens(t_token tokens[], int token_count, char **minishell_error_msg) {
    if (token_count == 0) return 0;

    // Vérifier si la commande commence par un opérateur de contrôle interdit
    if (is_control_operator(tokens[0].type)) {

        size_t msg_len = strlen("erreur de syntaxe près du symbole inattendu « ") + strlen(tokens[0].value) + strlen(" »\n") + 1;
        *minishell_error_msg = ft_calloc(msg_len, sizeof(char));
        ft_strcat(*minishell_error_msg, "erreur de syntaxe près du symbole inattendu «\u00A0");
        ft_strcat(*minishell_error_msg, tokens[0].value);
        ft_strcat(*minishell_error_msg, "\u00A0»\n");
        return 1;
    }

    for (int i = 0; i < token_count - 1; i++) {
        t_token_type current = tokens[i].type;
        t_token_type next = tokens[i + 1].type;

        // Vérifier si deux opérateurs de contrôle se suivent sans mot entre eux
        if (is_control_operator(current) && is_control_operator(next)) {
            //fprintf(stderr, "erreur de syntaxe près du symbole inattendu « %s »\n", tokens[i + 1].value);

            size_t msg_len = strlen("erreur de syntaxe près du symbole inattendu « ") + strlen(tokens[i + 1].value) + strlen(" »\n") + 1;
            *minishell_error_msg = ft_calloc(msg_len, sizeof(char));
            ft_strcat(*minishell_error_msg, "erreur de syntaxe près du symbole inattendu «\u00A0");
            ft_strcat(*minishell_error_msg, tokens[i + 1].value);
            ft_strcat(*minishell_error_msg, "\u00A0»\n");
            //printf("dzdijz: %s\n", *minishell_error_msg);
            return 1;
        }
    }

    // Vérifier si la commande se termine par un opérateur de contrôle (hors '&')
    //if (is_control_operator(tokens[token_count - 2].type) && tokens[token_count - 2].type != TOKEN_BACKGROUND) {
    //    //fprintf(stderr, "Erreur de syntaxe : La commande ne peut pas se terminer par '%s'\n", tokens[token_count - 2].value);
    //    return 1;
    //}

    return 0;
}