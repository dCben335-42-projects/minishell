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

int is_control_operator(t_token token) {
    t_token_type type = token.type;
    return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR ||
            type == TOKEN_SEMICOL || type == TOKEN_BACKGROUND ||
            type == TOKEN_PIPE_ERR || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT);
}

///**
// * Gère les erreurs de syntaxe de la commande
// * @param tokens: tableau de tokens
// * @param i: index du token
// * @param minishell_error_msg: message d'erreur
// */

//int handle_error(t_token tokens[], int i, char **minishell_error_msg)
//{
//    size_t msg_len = strlen("erreur de syntaxe près du symbole inattendu « ") + strlen(tokens[i].value) + strlen(" »\n") + 1;
//    *minishell_error_msg = ft_calloc(msg_len, sizeof(char));
//    ft_strcat(*minishell_error_msg, "erreur de syntaxe près du symbole inattendu «\u00A0");
//    ft_strcat(*minishell_error_msg, tokens[i].value);
//    ft_strcat(*minishell_error_msg, "\u00A0»\n");
//    return (1);
//}

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

///**
// * Vérifie si la commande est valide
// * @param tokens: tableau de tokens
// * @param token_count: nombre de tokens
// * @param minishell_error_msg: message d'erreur
// */

//int parse_tokens(t_token tokens[], int token_count, char **minishell_error_msg)
//{
//    int open_bracket_count = 0;
//    int close_bracket_count = 0;
    
//    if (token_count == 0) return 0;
//    if (is_control_operator(tokens[0].type))
//		return (handle_error(tokens, 0, minishell_error_msg));
//    for (int i = 0; i < token_count - 1; i++) {
//        t_token_type current = tokens[i].type;
//        t_token_type next = tokens[i + 1].type;

//        if (is_control_operator(current) && is_control_operator(next))
//			return (handle_error(tokens, i + 1, minishell_error_msg));
//        if (current == TOKEN_OPEN_BRACKET && next == TOKEN_CLOSE_BRACKET)
//			return (handle_error(tokens, i + 1, minishell_error_msg));
//        if (current == TOKEN_OPEN_BRACKET)
//        	open_bracket_count++;
//        else if (current == TOKEN_CLOSE_BRACKET)
//        	close_bracket_count++;
//        if (close_bracket_count > open_bracket_count)
//			return (handle_error(tokens, i, minishell_error_msg));
//    }
//    return 0;
//}

t_token *duplicate_token(const t_token *original) {
    if (original == NULL) {
        return NULL;
    }

    // Allouer de la mémoire pour la nouvelle structure t_token
    t_token *duplicate = malloc(sizeof(t_token));
    if (duplicate == NULL) {
        // Gérer l'erreur d'allocation si nécessaire
        return NULL;
    }

    // Copier le type du token
    duplicate->type = original->type;
    duplicate->value = original->value;

    return duplicate;
}

t_parse_status token_parser(t_lexer_args *args, char **error, t_token token)
{

    t_token prev_token;
    t_parser_static parser_static = {.is_init = FALSE};

    if (token.type == TOKEN_EOF && token.value && strcmp(token.value, "init") == 0)
    {
        //printf("init\n");
        parser_static.is_init = TRUE;
        parser_static.open_bracket_count = 0;
        parser_static.close_bracket_count = 0;
        //free(token.value);
        return (COMMAND_VALID);
    }

    if (args->token_count == 0)
    {
        if (is_control_operator(token))
            return(get_error_message(token, error));
    }
    else
    {
        //prev_token = (args->tokens[args->token_count - 1]);
        prev_token = *((t_token *)get_value(args->tokens, args->token_count - 1));
        if (is_control_operator(token) && is_control_operator(prev_token))
            return(get_error_message(token, error));

        // Only on depth 0, so to fix
        if (prev_token.type == TOKEN_OPEN_BRACKET && token.type == TOKEN_CLOSE_BRACKET)
            return(get_error_message(token, error));

        if (token.type == TOKEN_OPEN_BRACKET)
            parser_static.open_bracket_count++;
        else if (token.type == TOKEN_CLOSE_BRACKET)
            parser_static.close_bracket_count++;
        
        if (parser_static.close_bracket_count > parser_static.open_bracket_count)
            return(get_error_message(token, error));
    }

    set_value(args->tokens, args->token_count, duplicate_token(&token));
    args->token_count++;
    return (COMMAND_VALID);
}
