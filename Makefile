NAME = cub3d

# Lib
MLX_PATH = ./include/MLX42
MLX_NAME = libmlx42.a
MLX = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))
LIBFT_PATH = ./include/libft/
LIBFT_NAME = libft.a
LIBFT = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

# Sources
SRC = srcs/main.c srcs/parsing/parse_arg.c srcs/utils/parsing_utils.c
OBJ_DIR = obj
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

# Flags
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Loading bar setup
TOTAL_FILES := $(words $(SRC))
CURRENT_FILE := 0
BAR_LENGTH := 40

# Loading bar function
define update_loading_bar
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@$(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
	@$(eval PROGRESS=$(shell echo $$(($(CURRENT_FILE) * $(BAR_LENGTH) / $(TOTAL_FILES)))))
	@printf "\r%-100s" " "
	@printf "\r[%-$(BAR_LENGTH)s] %3d%% (%d/%d) $<" "$$(printf '%0.s#' $$(seq 1 $(PROGRESS)))" $(PERCENTAGE) $(CURRENT_FILE) $(TOTAL_FILES)
endef

# Règles de compilation
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(call update_loading_bar)
	@cc $(FLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_PATH)
	@cmake $(MLX_PATH) -B $(MLX_PATH)/build && make -C $(MLX_PATH)/build -j4

$(NAME): $(LIBFT) $(OBJ)
	@echo ""  # New line after loading bar
	@cc $(FLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "Compilation de $(NAME) réussie !"

clean:
	@make --no-print-directory clean -C $(LIBFT_PATH)
	@rm -rf $(OBJ_DIR)
	@echo "Directory cleaned !"

fclean: clean
	@make --no-print-directory fclean -C $(LIBFT_PATH)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re