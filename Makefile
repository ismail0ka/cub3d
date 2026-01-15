NAME=cub3d
CC=cc
CFLAGS=-Wall -Wextra -Werror -Iinclude  
# -fsanitize=address -g3
MLX_LIB=-lmlx -lXext -lX11 -lm
LIBFT_DIR=lib/libft
LIBFT=$(LIBFT_DIR)/libft.a

SRCS= src/main.c \
	src/parse_map.c \
	src/parse_map_utils.c \
	src/game/input_handler.c \
	src/game/player_mov.c \
	src/game/player_rot.c \
	src/game/player_init.c \
	src/game/check_collision.c \
	src/game/player_mov_utils.c \
	src/graphics/floor_n_ceiling.c \
	src/graphics/load_textures.c \
	src/graphics/raycasting.c \
	src/graphics/raycasting_utils.c \
	src/graphics/dda.c \
	src/graphics/render_map.c \
	src/graphics/render_map_utils.c \
	src/utils/color.c \
	src/utils/errors.c \
	src/parsing/check_map.c \
	src/parsing/check_map2.c \
	src/parsing/helper_utils.c \
	src/parsing/line_utils.c \
	src/parsing/map_cleanup.c \
	src/parsing/param_utils.c \
	src/parsing/parce_args.c \
	src/parsing/read_file.c \
	src/parsing/separate_elements_colors.c \
	src/parsing/separate_elements_map.c \
	src/parsing/separate_elements_map_utils.c \
	src/parsing/separate_elements_textures.c \
	src/parsing/separate_elements_textures2.c \
	src/parsing/separate_elements.c

OBJS= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
