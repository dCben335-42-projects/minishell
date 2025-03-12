NAME        = minishell

CC          = cc
C_FLAGS     = -Wall -Wextra -Werror

BUILD_DIR   = ./.build
RM = rm -rf
MKDIR = mkdir -p

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
			errors/basics.c \
			signals.c \
			env/init.c env/add.c env/get.c env/replace.c env/find.c env/destroy.c env/read.c \
			builtins/builtins.c builtins/callbacks/echo.c builtins/callbacks/cd.c builtins/callbacks/pwd.c builtins/callbacks/export.c builtins/callbacks/unset.c builtins/callbacks/env.c builtins/callbacks/exit.c \
			shell/init.c shell/destroy.c

			
SRC         = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ 		= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# rules
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(C_FLAGS) $(OBJ) -o $(NAME) $(LIBS_FLAGS) $(INCLUDES_FLAGS)
	
all: $(NAME) 
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) Makefile
	@$(MKDIR) $(@D)
	$(CC) $(C_FLAGS) -o $@ -c $< $(INCLUDES_FLAGS)

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

.PHONY: all clean fclean re force bonus norminette
