NAME = cub3D_parser

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = main.c \
       check_map.c \
       helper_utils.c \
       line_utils.c \
       map_cleanup.c \
       param_utils.c \
       parce_args.c \
       read_file.c \
       separate_elements_colors.c \
       separate_elements_map.c \
       separate_elements_textures.c \
       sparate_elements.c \
       temp_libft.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c parsing.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	@chmod +x run_tests.sh
	@bash run_tests.sh

.PHONY: all clean fclean re test
