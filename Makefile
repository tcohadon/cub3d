NAME       = cub3D
CC         = cc
SRC        = srcs/main.c \
             srcs/utils/utils.c \
             srcs/parsing/parse_arg.c \
             srcs/parsing/parse_init.c \
             srcs/parsing/parse_map.c \
             srcs/parsing/parsing_utils.c \
             srcs/parsing/verify_char.c \
             srcs/utils/utils2.c \
             srcs/exec/move_player.c \
             srcs/utils/parsing_utils.c \
             srcs/exec/render.c \
             srcs/utils/utils3.c \
             srcs/utils/utils4.c \
             srcs/utils/utils5.c \
             srcs/exec/dda.c \
             srcs/utils/hitbox.c \
             srcs/utils/render_utils.c \
             srcs/utils/render_utils2.c \
             srcs/utils/player_pos_init.c

OBJ_DIR    = obj
OBJ        = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

LIBFT_PATH = include/libft
MLX_PATH   = include/MLX42
MLX_LIB    = $(MLX_PATH)/build/libmlx42.a
LIBFT_LIB  = $(LIBFT_PATH)/libft.a

# Sur Linux, on n'utilise pas Homebrew, on peut donc supprimer la détection automatique
CFLAGS    = -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS   = -lglfw -lX11 -lXrandr -lXi -ldl -lm -pthread

# compile chaque .c
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

# build libft et mlx42
$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)
$(MLX_LIB):
	@cmake $(MLX_PATH) -B $(MLX_PATH)/build
	@make -C $(MLX_PATH)/build

# édition de liens
$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJ)
	@echo
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) $(LDFLAGS) -o $(NAME)
	@echo "Compilation réussie : $(NAME)"

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo "obj/ supprimé"

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(NAME) supprimé"

re: fclean all

.PHONY: all clean fclean re