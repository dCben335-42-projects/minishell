NAME        = minishell

CC          = cc
C_FLAGS     = -Wall -Wextra -Werror -g3

RM = rm -rf
MKDIR = mkdir -p
BUILD_DIR   = ./.build

# libs
LIBS_FOLDER = ./libs

LIBFT_FOLDER = $(LIBS_FOLDER)/libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_FOLDER)/$(LIBFT_NAME)
LIBFT_INCLUDE_FOLDER = $(LIBFT_FOLDER)/includes
LIBFT_FLAGS = -L $(LIBFT_FOLDER) -lft

LIBS_FLAGS = $(LIBFT_FLAGS) -lreadline -lhistory

# includes
INCLUDES_DIR = ./includes
INCLUDES_FILES = minishell.h messages.h errors.h env.h
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))
INCLUDES_FLAGS = -I $(INCLUDES_DIR) -I $(LIBFT_INCLUDE_FOLDER)

# sources
SRC_DIR     = ./srcs
SRC_FILES   = main.c \
			lexer/lexer.c lexer/handler_token.c lexer/parser.c \
			ast_builder/ast_builder.c ast_builder/add_cmd_utils.c ast_builder/get_cmd_master.c ast_builder/get_cmd.c ast_builder/get_or_and_cmd.c ast_builder/get_parenthesis_cmd.c ast_builder/get_pipe_cmd.c ast_builder/utils.c \
			cmd/cmd.c cmd/execute_cmd.c \
			errors/basics.c \
			signals.c \
			env/init.c env/destroy.c env/add.c env/parse.c env/get.c env/read.c \
			structs/dynamic_array/init.c structs/dynamic_array/destroy.c structs/dynamic_array/setter.c structs/dynamic_array/getter.c \
			structs/token/init.c structs/token/destroy.c structs/token/getter.c structs/token/is.c \
			structs/lexer_args/init.c structs/lexer_args/destroy.c \
			structs/ast_node/init.c structs/ast_node/destroy.c structs/ast_node/convert.c structs/ast_node/print.c \
			builtins/builtins.c builtins/callbacks/echo.c builtins/callbacks/cd.c builtins/callbacks/pwd.c builtins/callbacks/export.c builtins/callbacks/unset.c builtins/callbacks/env.c builtins/callbacks/exit.c \
			shell/init.c shell/destroy.c

			
SRC         = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ 		= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# rules
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(C_FLAGS) $(OBJ) -o $(NAME) $(INCLUDES_FLAGS) $(LIBS_FLAGS) 
	
all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) Makefile
	@$(MKDIR) $(@D)
	$(CC) $(C_FLAGS) -o $@ -c $< $(INCLUDES_FLAGS) $(LIBFT_FLAGS)

$(LIBFT): force
	$(MAKE) -C $(LIBFT_FOLDER)

clean:
	$(MAKE) clean -C $(LIBFT_FOLDER)
	$(RM) $(BUILD_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_FOLDER)
	$(RM) $(NAME)

re: fclean all

bonus: all

norm:
	$(MAKE) norm -C $(LIBFT_FOLDER)
	norminette $(SRC) $(INCLUDES)

force:
	@true

val: all
	valgrind --track-fds=all --suppressions=config/valgrind_ignore.conf --leak-check=full --show-leak-kinds=all --track-origins=yes -q -s ./$(NAME)

run: all
	./$(NAME)

-include config/forbidden.mk

.PHONY: all clean fclean re force bonus norminette val run
