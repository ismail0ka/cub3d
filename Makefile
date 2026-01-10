NAME=cub3d
CC=cc
CFLAGS=-Wall -Wextra -Werror -Iinclude
MLX_LIB=-lmlx -lXext -lX11 -lm

SRCS := \
	src/main.c \
	src/parse_map.c \
	src/game/input_handler.c \
	src/game/player.c \
	src/graphics/floor_n_ceiling.c \
	src/graphics/load_textures.c \
	src/graphics/raycasting.c \
	src/graphics/render_map.c \
	src/utils/color.c \
	src/utils/errors.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
