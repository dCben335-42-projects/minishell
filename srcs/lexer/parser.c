#include "parser_lexer.h"

/**
 * Concatène deux chaînes de caractères
 * @param dest: chaîne de destination
 * @param src: chaîne source
 */
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
 * Vérifie si le token est un opérateur de contrôle
 * @param token: token à vérifier
 */
int is_control_operator(t_token *token) {
    t_token_type type = token->type;
    return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR ||
            type == TOKEN_SEMICOL || type == TOKEN_BACKGROUND ||
            type == TOKEN_PIPE_ERR || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT);
}

/**
 * Génère un message d'erreur
 * @param token: token invalide
 * @param error: message d'erreur
 */
t_parse_status get_error_message(t_token token, char **error)
{
    size_t msg_len = strlen("erreur de syntaxe près du symbole inattendu « ") + strlen(token.value) + strlen(" »\n") + 1;
    *error = ft_calloc(msg_len, sizeof(char));
    ft_strcat(*error, "erreur de syntaxe près du symbole inattendu «\u00A0");
    ft_strcat(*error, token.value);
    ft_strcat(*error, "\u00A0»\n");
    return (COMMAND_NOT_VALID);
}

/**
 * Duplique un token
 * @param original: token à dupliquer
 * @return le token dupliqué
 */
t_token *duplicate_token(const t_token *original) {
    if (original == NULL)
        return (NULL);
    t_token *duplicate = malloc(sizeof(t_token));
    if (duplicate == NULL)
        return (NULL);
    duplicate->type = original->type;
    duplicate->value = original->value;
    return (duplicate);
}

/**
 * Fonction pour analyser les tokens
 * @param args: arguments du lexer
 * @param error: message d'erreur
 * @param token: token à analyser
 * @return le statut de la commande
 */
t_parse_status token_parser(t_lexer_args *args, char **error, t_token *token)
{

    //t_token prev_token;
    static t_parser_static parser_static = {.is_init = FALSE};

    if (!parser_static.is_init)
    {
        parser_static.is_init = TRUE;
        parser_static.open_parenthesis_count = 0;
        parser_static.close_parenthesis_count = 0;
        free(token->value);
        free(token);
        return (COMMAND_VALID);
    }
    if (args->tokens.count == 0)
    {
        if (is_control_operator(token))
            return(get_error_message(*token, error));
    }
    //else
    //{
    //    prev_token = *((t_token *)get_value(&args->tokens, args->tokens.count - 1));
    //    if (is_control_operator(*token) && is_control_operator(prev_token))
    //        return(get_error_message(*token, error));

    //    if (prev_token.type == TOKEN_OPEN_BRACKET && token->type == TOKEN_CLOSE_BRACKET)
    //        return(get_error_message(*token, error));

    //    if (token->type == TOKEN_OPEN_BRACKET)
    //        parser_static.open_parenthesis_count++;
    //    else if (token->type == TOKEN_CLOSE_BRACKET)
    //        parser_static.close_parenthesis_count++;
        
    //    if (parser_static.close_parenthesis_count > parser_static.open_parenthesis_count)
    //        return(get_error_message(*token, error));
    //}

    set_value(&args->tokens, args->tokens.count, token);
    return (COMMAND_VALID);
}
