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
 * Vérifie si un token est un opérateur de contrôle (&&, ||, |, ;, etc.)
 * @param type: type de token
 */

int is_control_operator(t_token_type type) {
    return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR ||
            type == TOKEN_SEMICOL || type == TOKEN_BACKGROUND ||
            type == TOKEN_PIPE_ERR || type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT);
}

/**
 * Gère les erreurs de syntaxe de la commande
 * @param tokens: tableau de tokens
 * @param i: index du token
 * @param minishell_error_msg: message d'erreur
 */

int handle_error(t_token tokens[], int i, char **minishell_error_msg)
{
    size_t msg_len = strlen("erreur de syntaxe près du symbole inattendu « ") + strlen(tokens[i].value) + strlen(" »\n") + 1;
    *minishell_error_msg = ft_calloc(msg_len, sizeof(char));
    ft_strcat(*minishell_error_msg, "erreur de syntaxe près du symbole inattendu «\u00A0");
    ft_strcat(*minishell_error_msg, tokens[i].value);
    ft_strcat(*minishell_error_msg, "\u00A0»\n");
    return (1);
}

/**
 * Vérifie si la commande est valide
 * @param tokens: tableau de tokens
 * @param token_count: nombre de tokens
 * @param minishell_error_msg: message d'erreur
 */

int parse_tokens(t_token tokens[], int token_count, char **minishell_error_msg)
{
    int open_bracket_count = 0;
    int close_bracket_count = 0;
    
    if (token_count == 0) return 0;
    if (is_control_operator(tokens[0].type))
		return (handle_error(tokens, 0, minishell_error_msg));
    for (int i = 0; i < token_count - 1; i++) {
        t_token_type current = tokens[i].type;
        t_token_type next = tokens[i + 1].type;

        if (is_control_operator(current) && is_control_operator(next))
			return (handle_error(tokens, i + 1, minishell_error_msg));
        if (current == TOKEN_OPEN_BRACKET && next == TOKEN_CLOSE_BRACKET)
			return (handle_error(tokens, i + 1, minishell_error_msg));
        if (current == TOKEN_OPEN_BRACKET)
        	open_bracket_count++;
        else if (current == TOKEN_CLOSE_BRACKET)
        	close_bracket_count++;
        if (close_bracket_count > open_bracket_count)
			return (handle_error(tokens, i, minishell_error_msg));
    }
    return 0;
}
