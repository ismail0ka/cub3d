#include <string.h>
#include "cub3d.h"

void  init_renderer(t_renderer *renderer, t_mlx *mlx, t_map *map)
{
	int i;

	(void)map;
	if (!renderer || !mlx)
		return;
	i = 0;
	while (i < NUM_TEXTURES)
	{
		memset(&renderer->textures[i], 0, sizeof(renderer->textures[i]));
		i++;
	}
	i = 0;
	while (i < MAX_WIDTH)
	{
		renderer->z_buffer[i] = 0.0;
		i++;
	}
	(void)mlx;
}
