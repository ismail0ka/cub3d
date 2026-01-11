#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"

void  cleanup_engine(t_engine *engine)
{
	int i;

	if (!engine)
		return;
	if (engine->renderer && engine->mlx)
	{
		i = 0;
		while (i < NUM_TEXTURES)
		{
			if (engine->renderer->textures[i].img)
				mlx_destroy_image(engine->mlx->mlx, engine->renderer->textures[i].img);
			i++;
		}
	}
	if (engine->mlx)
	{
		if (engine->mlx->win)
			mlx_destroy_window(engine->mlx->mlx, engine->mlx->win);
		if (engine->mlx->mlx)
			mlx_destroy_display(engine->mlx->mlx);
		free(engine->mlx);
	}
	if (engine->map)
	{
		free(engine->map->no_texture);
		free(engine->map->so_texture);
		free(engine->map->we_texture);
		free(engine->map->ea_texture);
		free(engine->map->floor_color);
		free(engine->map->ceiling_color);
		free_2d_array(engine->map->layout);
		free(engine->map);
	}
	if (engine->renderer)
		free(engine->renderer);
	if (engine->player)
		free(engine->player);
}

void  exit_with_error(const char *error_message, t_engine *engine)
{
	if (error_message)
		printf("Error: %s\n", error_message);
	cleanup_engine(engine);
	exit(EXIT_FAILURE);
}
