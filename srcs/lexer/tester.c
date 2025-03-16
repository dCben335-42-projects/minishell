//#include "parser_lexer.h"

//#define TEST_COUNT 18
//#define ERROR_BUFFER_SIZE 1024

//int check_bash_syntax(const char *command, char *bash_error_msg) {
//    char cmd[256];
//    //snprintf(cmd, sizeof(cmd), "bash -n -c '%s' 2>&1", command); // Capture stderr
//    snprintf(cmd, sizeof(cmd), "bash -n -c '%s' 2>&1", command);
//    FILE *fp = popen(cmd, "r");
//    if (!fp) return 1;

//    // Lire la première ligne du message d'erreur
//    if (fgets(bash_error_msg, ERROR_BUFFER_SIZE, fp) != NULL) {
//        // Supprime "bash: -c: ligne 1: " du début du message
//        char *error_start = strstr(bash_error_msg, "ligne");
//        while (*error_start && *error_start != ':') {
//            error_start++;
//        }
//        error_start += 2;
//        if (error_start) {
//            memmove(bash_error_msg, error_start, strlen(error_start) + 1);
//        }
//    } else {
//        bash_error_msg[0] = '\0'; // Aucun message d'erreur
//    }

//    int result = pclose(fp);
//    return result != 0;
//}

//void message_error_handler(int test_id, int error_code, const char *mini_error_msg, const char *bash_error_msg)
//{
//    if (error_code == 1)
//        printf("❌ Test %d échoué : Code de retour différent de Bash\n", test_id);
//    else
//        printf("❌ Test %d échoué : Message d'erreur différent de Bash\n", test_id);
//    if (mini_error_msg != NULL)
//        printf("MINI_ERROR: %s", mini_error_msg);
//    else
//        printf("MINI_ERROR: (null)\n");
//    if (bash_error_msg[0] != '\0')
//        printf("BASH_ERROR: %s", bash_error_msg);
//    else
//        printf("BASH_ERROR: (null)\n");
//}

//int main() {
//    const char *test_commands[TEST_COUNT] = {
//        "'", // Valide
//        "ls -l && && dzdzd", // Valide
//        "'main.c'", // Valide
//        "\"main.c$COUCOU\"", // Valide
//        "\"main.c c\\'est gotty\"", // Valide
//        "\"main.c 'fef'\"", // Valide
//        "\"*.c\"", // Valide
//        "*.c", // Valide
//        "echo 'C'\"'\"'est un test'", // Valide BUG avec sh
//        "ls -l | grep 'main.c' && echo Done > output.txt", // Valide
//        "ls -l ||| grep main.c", // Invalide
//        "echo 'test' > < file", // Invalide
//        "cat file.txt &&", // Invalide (se termine par &&)
//        "echo Hello ; ; echo World", // Invalide (double ;)
//        "& echo Hello ;",
//        "(echo Hello ; echo World) && echo Done", // Valide
//        ")echo Hello ; echo World) && echo Done", // Valide
//        "()"
//    };

//    for (int i = 0; i < TEST_COUNT; i++) {
//        printf("\nTest %d: %s\n", i + 1, test_commands[i]);
//        t_token tokens[MAX_TOKENS];
//        int token_count = 0;
//        char bash_error_msg[ERROR_BUFFER_SIZE] = {0};
//        char *mini_error_msg = NULL;

//        lexer(test_commands[i], tokens, &token_count);
//        print_tokens(tokens, token_count);

//        int my_parser_result = parse_tokens(tokens, token_count, &mini_error_msg);
//        int bash_result = check_bash_syntax(test_commands[i], bash_error_msg);
//        //if (my_parser_result == bash_result)
//        //{
//            if ((mini_error_msg == NULL && bash_error_msg[0] == '\0')
//                || (mini_error_msg && bash_error_msg[0] && strcmp(mini_error_msg, bash_error_msg) == 0))
//                printf("✅ Test %d réussi\n", i + 1);
//            else
//                message_error_handler(i + 1, 0, mini_error_msg, bash_error_msg);
//        //}
//        //else
//        //    message_error_handler(i + 1, 1, mini_error_msg, bash_error_msg);
//    }
//    return 0;
//}

//// Commande pour compiler:
//// cc main.c lexer.c parser.c -I ../../libs/libft/includes -I ../../includes  ../../libs/libft/srcs/**/*.c