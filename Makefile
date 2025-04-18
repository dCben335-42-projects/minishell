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

INCLUDES_FILES = errors.h messages.h minishell.h
INCLUDES_FILES += cmd.h cmd_builtin.h cmd_expand.h
INCLUDES_FILES += struct_wildcard.h struct_lexer_args.h struct_token.h struct_shell.h struct_env.h struct_dynarray.h

INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))
INCLUDES_FLAGS = -I $(INCLUDES_DIR) -I $(LIBFT_INCLUDE_FOLDER)

# sources
SRC_DIR     = ./srcs

SRC_STRUCTS_DIR = ./structs
SRC_PARSING_DIR = ./parsing
SRC_EXEC_DIR = ./exec
SRC_BUILTINS_DIR = $(SRC_EXEC_DIR)/run/builtins
SRC_EXPAND_DIR = $(SRC_EXEC_DIR)/expand

SRC_FILES   = main.c signals.c errors.c

SRC_FILES += $(SRC_PARSING_DIR)/lexer.c $(SRC_PARSING_DIR)/parser.c $(SRC_PARSING_DIR)/handler_token.c 

SRC_FILES += $(SRC_EXEC_DIR)/cmd.c
SRC_FILES += $(SRC_EXPAND_DIR)/expand.c $(SRC_EXPAND_DIR)/env/env.c $(SRC_EXPAND_DIR)/wildcard/match/match.c $(SRC_EXPAND_DIR)/wildcard/wildcard.c $(SRC_EXPAND_DIR)/wildcard/match/entry.c $(SRC_EXPAND_DIR)/wildcard/match/path.c
SRC_FILES += $(SRC_BUILTINS_DIR)/builtins.c $(SRC_BUILTINS_DIR)/callbacks/echo.c $(SRC_BUILTINS_DIR)/callbacks/cd.c $(SRC_BUILTINS_DIR)/callbacks/pwd.c $(SRC_BUILTINS_DIR)/callbacks/export.c $(SRC_BUILTINS_DIR)/callbacks/unset.c $(SRC_BUILTINS_DIR)/callbacks/env.c $(SRC_BUILTINS_DIR)/callbacks/exit.c \
	
SRC_FILES += $(SRC_STRUCTS_DIR)/dynarray/init.c $(SRC_STRUCTS_DIR)/dynarray/destroy.c $(SRC_STRUCTS_DIR)/dynarray/setter.c $(SRC_STRUCTS_DIR)/dynarray/getter.c
SRC_FILES += $(SRC_STRUCTS_DIR)/token/init.c $(SRC_STRUCTS_DIR)/token/destroy.c $(SRC_STRUCTS_DIR)/token/getter.c $(SRC_STRUCTS_DIR)/token/is.c
SRC_FILES += $(SRC_STRUCTS_DIR)/lexer_args/init.c $(SRC_STRUCTS_DIR)/lexer_args/destroy.c
SRC_FILES += $(SRC_STRUCTS_DIR)/shell/init.c $(SRC_STRUCTS_DIR)/shell/destroy.c
SRC_FILES += $(SRC_STRUCTS_DIR)/env/init.c $(SRC_STRUCTS_DIR)/env/destroy.c $(SRC_STRUCTS_DIR)/env/add.c $(SRC_STRUCTS_DIR)/env/parse.c $(SRC_STRUCTS_DIR)/env/get.c $(SRC_STRUCTS_DIR)/env/read.c
SRC_FILES += $(SRC_STRUCTS_DIR)/wildcard/init.c $(SRC_STRUCTS_DIR)/wildcard/destroy.c $(SRC_STRUCTS_DIR)/wildcard/is_valid.c $(SRC_STRUCTS_DIR)/wildcard/prefix.c $(SRC_STRUCTS_DIR)/wildcard/suffix.c $(SRC_STRUCTS_DIR)/wildcard/tree/init.c $(SRC_STRUCTS_DIR)/wildcard/tree/add.c

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
