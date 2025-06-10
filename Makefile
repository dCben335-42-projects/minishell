NAME        = minishell

CC          = cc
C_FLAGS     = -Wall -Wextra -Werror

RM = rm -rf
MKDIR = mkdir -p
BUILD_DIR   = ./.build

CONF_DIR   = ./config
CONF_VALGRIND = $(CONF_DIR)/valgrind_ignore.conf
CONF_MK_FORBIDDEN = $(CONF_DIR)/forbidden.mk
CONF_MK_INCLUDES = $(CONF_DIR)/includes.mk
CONF_MK_SOURCES = $(CONF_DIR)/sources.mk

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
INCLUDES_FILES :=
-include $(CONF_MK_INCLUDES)

INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))
INCLUDES_FLAGS = -I $(INCLUDES_DIR) -I $(LIBFT_INCLUDE_FOLDER)

# sources
SRC_DIR		= ./srcs
SRC_FILES	:=
-include $(CONF_MK_SOURCES)

SRC         = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ 		= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# rules
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(C_FLAGS) $(OBJ) -o $(NAME) $(INCLUDES_FLAGS) $(LIBS_FLAGS) 
	
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
	norminette $(SRC_DIR) $(INCLUDES_DIR)

force:
	@true

val: all
	valgrind --suppressions=$(CONF_VALGRIND) --track-fds=all --leak-check=full --show-leak-kinds=all --track-origins=yes -q -s ./$(NAME) 

run: all
	./$(NAME)

gen:
	@$(MKDIR) $(CONF_DIR)
	@echo "Generating includes.mk..."
	@./config/generate_mk.sh $(INCLUDES_DIR) "*.h" $(CONF_MK_INCLUDES) INCLUDES_FILES
	@echo "Generating sources.mk..."
	@./config/generate_mk.sh $(SRC_DIR) "*.c" $(CONF_MK_SOURCES) SRC_FILES
	$(MAKE)

-include $(CONF_MK_FORBIDDEN)

.PHONY: all clean fclean re force bonus norminette val run gen
