NAME=cub3d
CC=cc
CFLAGS=-Wall -Wextra -Werror -Iinclude -g3
MLX_LIB=-lmlx -lXext -lX11 -lm
LIBFT=libft.a

SRCS= src/main.c \
	src/parse_map.c \
	src/game/input_handler.c \
	src/game/player.c \
	src/graphics/floor_n_ceiling.c \
	src/graphics/load_textures.c \
	src/graphics/raycasting.c \
	src/graphics/render_map.c \
	src/utils/color.c \
	src/utils/errors.c \
	src/parsing/check_map.c \
	src/parsing/helper_utils.c \
	src/parsing/line_utils.c \
	src/parsing/map_cleanup.c \
	src/parsing/param_utils.c \
	src/parsing/parce_args.c \
	src/parsing/read_file.c \
	src/parsing/separate_elements_colors.c \
	src/parsing/separate_elements_map.c \
	src/parsing/separate_elements_textures.c \
	src/parsing/sparate_elements.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C lib/libft

$(MLX):
	$(MAKE) -C lib/minilibx-linux

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) lib/libft/$(LIBFT) $(MLX_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
