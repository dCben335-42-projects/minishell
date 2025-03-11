#include "parser_lexer.h"

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
    },
    {
        '\'', // Single quote
        {
            {'\0', TOKEN_QUOTE}
        }
    },
    {
        '"', // Double quote
        {
            {'\0', TOKEN_DQUOTE}
        }
    },
    {
        '(', // Left bracket
        {
            {'\0', TOKEN_OPEN_BRACKET}
        }
    },
    {
        ')', // Right bracket
        {
            {'\0', TOKEN_CLOSE_BRACKET}
        }
    }
};

t_token_name token_names[] = {
    {"TEXT"},
    {"VAR_TEXT"},
    {"LITERAL_TEXT"},
    {"PIPE"},
    {"AND"},
    {"OR"},
    {"SEMICOL"},
    {"REDIR_IN"},
    {"REDIR_OUT"},
    {"APPEND"},
    {"BACKGROUND"},
    {"PIPE_ERR"},
    {"QUOTE"},
    {"DQUOTE"},
    {"BRACKET_LEFT"},
    {"BRACKET_RIGHT"},
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
    return (TOKEN_TEXT);
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
 * Fonction pour gérer les tokens entre guillemets
 * @param i: index de la chaîne d'entrée
 * @param len: longueur de la chaîne d'entrée
 * @param args: arguments du lexer
 * @param type: type de token
 */

void handler_token_quoted(int *i, int len, t_lexer_args *args, t_token_type type)
{
    int start_i;
    
    *i++;
    start_i = *i;
    while (*i < len && (start_i == *i || find_token_type(&args->input[*i], 0) != type))
        *i++;
    *i++;
    if (type == TOKEN_QUOTE)
        return (t_token){TOKEN_LITERAL_TEXT, ft_strndup(&args->input[start_i], *i - start_i - 1)};
    else
        return (t_token){TOKEN_VAR_TEXT, ft_strndup(&args->input[start_i], *i - start_i - 1)};
}

/**
 * Fonction pour analyser la chaîne d'entrée et générer des tokens
 * @param input: chaîne d'entrée
 * @param tokens: tableau de tokens
 * @param token_count: nombre de tokens
 */

void lexer(t_lexer_args *args)
{
    int i;
    int len;
    int offset;
    int start_i;

    i = 0;
    len = ft_strlen(args->input);

    while (i < len)
    {
        if (isspace(args->input[i]))
        { 
            i++; 
            continue; 
        }
        offset = 0;
        t_token_type type = find_token_type(&args->input[i], &offset);

        if (type == TOKEN_QUOTE || type == TOKEN_DQUOTE)
            token_parser(handler_token_quoted(&i, len, args, type));
        else if (type != TOKEN_TEXT)
        {
            token_parser((t_token){type, ft_strndup(&args->input[i], offset + 1)});
            i += (offset + 1);
        }
        else
        {
            start_i = i;
            while (i < len && !isspace(args->input[i]) && find_token_type(&args->input[i], &offset) == TOKEN_TEXT)
                i++;
            token_parser((t_token){TOKEN_TEXT, ft_strndup(&args->input[start_i], i - start_i)});
        }
    }




    //args->token_count++;
    //while (i < len)
    //{
    //    if (isspace(args->input[i]))
    //    { 
    //        i++; 
    //        continue; 
    //    }
    //    offset = 0;
    //    t_token_type type = find_token_type(&args->input[i], &offset);

    //    //printf("type: %d\n", type);

    //    if (type == TOKEN_DQUOTE)
    //    {
    //        i++;
    //        start_i = i;
    //        while (i < len && (start_i == i || find_token_type(&args->input[i], &offset) != TOKEN_DQUOTE))
    //            i++;
    //        lexer_setter(args->tokens, args->token_count, TOKEN_VAR_TEXT, ft_strndup(&args->input[start_i], i - start_i));
    //        i++;
    //    }
    //    else if (type == TOKEN_QUOTE)
    //    {
    //        i++;
    //        start_i = i;
    //        while (i < len && (start_i == i || find_token_type(&args->input[i], &offset) != TOKEN_QUOTE))
    //            i++;
    //        lexer_setter(args->tokens, args->token_count, TOKEN_LITERAL_TEXT, ft_strndup(&args->input[start_i], i - start_i));
    //        i++;
    //    }
    //    else if (type != TOKEN_TEXT)
    //    {
    //        lexer_setter(args->tokens, args->token_count, type, ft_strndup(&args->input[i], offset + 1));
    //        i += (offset + 1);
    //    }
    //    else
    //    {
    //        start_i = i;
    //        while (i < len && !isspace(args->input[i]) && find_token_type(&args->input[i], &offset) == TOKEN_TEXT)
    //            i++;
    //        lexer_setter(args->tokens, args->token_count, TOKEN_TEXT, ft_strndup(&args->input[start_i], i - start_i));
    //    }
    //}
    //lexer_setter(args->tokens, args->token_count, TOKEN_EOF, ft_strdup("EOF"));
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
