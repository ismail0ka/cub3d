#include "parsing.h"

/*
** REQUIRED LIBRARIES:
** - libft (with functions: ft_strlen, ft_strdup, ft_split, ft_substr, 
**          ft_strncmp, ft_isdigit, ft_atoi, ft_putstr_fd)
** - get_next_line
** 
** COMPILATION:
** cc -Wall -Wextra -Werror *.c -L../libft -lft -o cub3D_parser
*/

static void	print_map(char **map)
{
	int	i;

	if (!map)
		return ;
	printf("\n=== MAP ===\n");
	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		if (map[i][ft_strlen(map[i]) - 1] != '\n')
			printf("\n");
		i++;
	}
}

static void	print_textures(char **textures)
{
	printf("\n=== TEXTURES ===\n");
	printf("North (NO): %s\n", textures[NORTH_TEX]);
	printf("South (SO): %s\n", textures[SOUTH_TEX]);
	printf("West  (WE): %s\n", textures[WEST_TEX]);
	printf("East  (EA): %s\n", textures[EAST_TEX]);
}

static void	print_colors(int *floor, int *ceiling)
{
	printf("\n=== COLORS ===\n");
	printf("Floor   (F): RGB(%d, %d, %d)\n", floor[0], floor[1], floor[2]);
	printf("Ceiling (C): RGB(%d, %d, %d)\n", ceiling[0], ceiling[1], ceiling[2]);
}

static void	print_player(t_playerdata *player)
{
	printf("\n=== PLAYER ===\n");
	printf("Position: Cell[%d, %d] Pixel[%d, %d]\n",
		player->cell_x, player->cell_y,
		player->pixel_x, player->pixel_y);
	printf("Direction: %c\n", player->direction);
}

static void	print_parsed_data(t_params *params)
{
	printf("\n");
	printf("========================================\n");
	printf("      PARSING RESULTS\n");
	printf("========================================\n");
	
	print_textures(params->textures);
	print_colors(params->floor_color, params->ceiling_color);
	print_player(params->player);
	print_map(params->map);
	
	printf("\n========================================\n");
	printf("      PARSING SUCCESSFUL!\n");
	printf("========================================\n\n");
}

int	main(int ac, char **av)
{
	t_params		*params;
	t_playerdata	player;
	t_raydata		ray;

	if (ac != 2)
	{
		printf("Usage: %s <map.cub>\n", av[0]);
		return (1);
	}
	
	params = params_holder();
	if (!params)
	{
		perror("cub3D");
		return (1);
	}
	
	params_init(&params, &ray, &player);
	
	if (parse_args(av[1]) == -1)
	{
		printf("\nError\nFailed to parse %s\n", av[1]);
		free_params(&params);
		return (1);
	}
	
	print_parsed_data(params);
	
	free_params(&params);
	return (0);
}
