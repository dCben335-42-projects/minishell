#include "parser_lexer.h"

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
 * Fonction pour dupliquer une chaîne de caractères
 * @param str: chaîne d'entrée
 * @param n: nombre de caractères à copier
 */

char *ft_strndup(const char *str, size_t n)
{
    char *new_str;
    size_t len;

    len = strlen(str);
    if (n < len)
        len = n;
    new_str = malloc(len + 1);
    if (!new_str)
        return (NULL);
    new_str[len] = '\0';
    return ((char *)ft_memcpy(new_str, str, len));
}

/**
 * Fonction pour placer un token dans le tableau de tokens
 * @param tokens: tableau de tokens
 * @param token_count: empacement du token
 * @param type: type de token
 * @param value: valeur du token
 */

void lexer_setter(t_token tokens[], int *token_count, t_token_type type, char *value)
{
    tokens[*token_count].type = type;
    tokens[*token_count].value = value;
    (*token_count)++;
}

/**
 * Fonction pour analyser la chaîne d'entrée et générer des tokens
 * @param input: chaîne d'entrée
 * @param tokens: tableau de tokens
 * @param token_count: nombre de tokens
 */

void lexer(const char *input, t_token tokens[], int *token_count)
{
    int i;
    int len;
    int offset;
    int start_i;

    i = 0;
    len = ft_strlen(input);
    *token_count = 0;
    while (i < len)
    {
        if (isspace(input[i]))
        { 
            i++; 
            continue; 
        }
        offset = 0;
        t_token_type type = find_token_type(&input[i], &offset);
        if (type != TOKEN_WORD)
        {
            lexer_setter(tokens, token_count, type, ft_strndup(&input[i], offset + 1));
            i += (offset + 1);
        }
        else
        {
            start_i = i;
            while (i < len && !isspace(input[i]) && find_token_type(&input[i], &offset) == TOKEN_WORD)
                i++;
            lexer_setter(tokens, token_count, TOKEN_WORD, ft_strndup(&input[start_i], i - start_i));
        }
    }
    lexer_setter(tokens, token_count, TOKEN_EOF, ft_strdup("EOF"));
}

/**
 * Fonction pour afficher les tokens
 * @param tokens: tableau de tokens
 * @param count: nombre de tokens
 */

void print_tokens(t_token tokens[], int count)
{
    for (int i = 0; i < count; i++) {
        printf("Token: %-12s | Type: %s\n", tokens[i].value, token_names[tokens[i].type].name);
    }
}
