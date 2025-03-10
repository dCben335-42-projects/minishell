#include "parser_lexer.h"

int main() {
    //const char *command = "ls -l |& grep \"main.c\" && echo \"Done\" > output.txt";
    const char *command = "ls -l | grep \"main.c\" && echo \"Done\" > output.txt";
    t_token tokens[MAX_TOKENS];
    int token_count = 0;

    lexer(command, tokens, &token_count);
    print_tokens(tokens, token_count);

    if (parse_tokens(tokens, token_count) == 0) {
        printf("Syntaxe correcte.\n");
    }
    return 0;
}

// Commande pour compiler:
// cc main.c lexer.c parser.c -I ../../libs/libft/includes -I ../../includes  ../../libs/libft/srcs/**/*.c