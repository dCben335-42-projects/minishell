#include "ast.h"
#include "dynamic_array.h"
#include "token.h"
#include <stdlib.h>
#include "parser_lexer.h"

int main() {
	t_dynamic_array	*cmd_master;
	t_dynamic_array *tokens;
	t_parse_status status;
	t_lexer_args args;

	//const char *command = "(ls | cat | ba && co | ga) | cat | josd | ls";
	//const char *command = "(ls | cat | ba << co | ga) | cat | josd | ls";
	//const char *command = "true || ( echo 'A' && echo 'B' )";
	//const char *command = "(true || echo 'A') && echo 'B'";
	//const char *command = "(true || echo 'A') && echo 'B'";
	//const char *command = "true || cat";
	//const char *command = "(true || cat)";
	//const char *command = "true || echo 'A' && echo 'B' && echo 'B'";
	//const char *command = "true >> echo 'A' >> echo 'B'";
	//const char *command = "ls | cat | ba | ca | ga";
	//const char *command = "echo 'bonjour' && ( echo 'jojo' )";
	//const char *command = "echo 'bonjour' && ( echo no && echo po )";
	//const char *command = "echo 'bonjour' && ( echo no )";
	//const char *command = "echo 'bonjour' && ( echo no )";
	//const char *command = "(((echo 'salut')&&(echo 'hello'))&& echo 'bonjour')";
	//const char *command = "(((echo 'salut')&&(echo 'hello'))&&echo 'bonjour')";
	//const char *command = "( ( ( echo 'salut' ) ) && echo 'bonjour' )";
	// const char *command = "find ~ -type f -size +100M -print0 | tar --null -czf - --files-from=- | openssl enc -aes-256-cbc -salt -pass pass:secret -out ~/backup.enc && sha256sum ~/backup.enc >> ~/sha256.log && notify-send \"Backup\" \"Done\"";
	
	// const char *command = "(find ~ -type f -size +50M ! -name \"*.mp4\" -print0 | tar --null -czf - --files-from=-) \
	// | 	( \
	// 	openssl enc -aes-256-cbc -salt -pass pass:secret -out \
	// 	&& archive=~/backup_$(date +%Y%m%d_%H%M%S).enc \
	// 	&& 	( \
	// 			du -h \"$archive\" \
	// 			&& sha256sum \"$archive\" \
	// 	 	) \
	// 		>> ~/backup.log \
	// 	&& notify-send \"✅ Backup Success\" \"$archive archived & encrypted\" \
	// 	) \
	// || (notify-send \"❌ Backup Failed\" \"An error occurred during backup\")";

	// const char *command =
	// "bash -c "
	// "log=~/backup.log && "
	// "timestamp=$(date +%Y%m%d_%H%M%S) && "
	// "archive=~/backup_$timestamp.enc && "
	// "find ~ -type f -size +50M ! -name \\\"*.mp4\\\" -print0 "
	// "| tar --null -czf - --files-from=- "
	// "| openssl enc -aes-256-cbc -salt -pass pass:secret -out $archive "
	// "&& du -h $archive >> $log "
	// "&& sha256sum $archive >> $log "
	// "&& echo [✔] Backup created at $(date) >> $log "
	// "&& notify-send \\\"✅ Backup\\\" \\\"Success: $archive\\\" "
	// "|| (echo [✘] Backup failed at $(date) >> $log && notify-send \\\"❌ Backup\\\" \\\"Failure: See log\\\")"
	// "";
	
	const char *command = "echo";
	
	

	//args = init_lexer_args("true || (echo 'A' && echo 'B')");
	//args = init_lexer_args("ls -l && echo 'hello' && cat file.txt | output.txt && echo 'jojo' || echo 'tata'");
	//args = init_lexer_args("ls -l && echo 'hello' && cat file.txt | output.txt | momo.txt && echo 'jojo' || echo 'tata'");
	//args = init_lexer_args("dzidziu\"$PATH\""); // ajouter les espaces au token
	//args = init_lexer_args("echo \"bonjour\" && ( echo \"jojo\" && echo \"pipi\" ) || cat file.txt | output.txt | momo.txt | toto.txt | jiji.txt && echo \"jojo\" && echo \"toto\"");
	//args = init_lexer_args("echo \"bonjour\" && ( echo \"jojo\" || ( echo \"lord\" && echo \"dart\" ) && (echo \"pipi\") )" );
	//args = init_lexer_args("( echo \"bonjour\" &&  echo \"jojo\" )");
	//args = init_lexer_args("( ls && cat file.txt && echo 'hello') || (echo 'jojo' && echo 'tata' && (echo 'toto' 'tata'))");
	//args = init_lexer_args("echo \"bonjour\"");

	args = init_lexer_args(command);
	status = lexer(&args);
	if (status != COMMAND_VALID)
	{
		printf("Error: %s\n", (&args)->error);
		return (0);
	}
	print_tokens(&(&args)->tokens);
	printf("command=%s\n", command);
	tokens = &args.tokens;

	cmd_master = get_cmd_master((t_get_cmd_master){tokens, 0, tokens->count - 1});
	print_ast_json_wrapper(cmd_master);
	destroy_dynamic_array(cmd_master);
	destroy_dynamic_array(tokens);


	//recursive_destroy_node(get_value(cmd_master, 0));
	//recursive_destroy_node(get_value(cmd_master, 1));
	//recursive_destroy_node(get_value(cmd_master, 2));
	//recursive_destroy_node(get_value(cmd_master, 3));
	//recursive_destroy_node(get_value(cmd_master, 4));
	//recursive_destroy_node(get_value(cmd_master, 5));
	//free(cmd_master->data);
	//free(cmd_master);


    return (0);
}

//cc srcs/ast_builder/*.c libs/libft/srcs/**/*.c srcs/structs/**/*.c srcs/lexer/*.c -I includes -I libs/libft/includes