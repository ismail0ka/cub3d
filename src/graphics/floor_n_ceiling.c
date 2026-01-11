#include "cub3d.h"

static void put_pixel_to_image(t_renderer *renderer, int x, int y, int color)
{
	char *dst;
	int offset;

	if (!renderer || !renderer->addr)
		return;
	offset = y * renderer->line_len + x * (renderer->bpp / 8);
	dst = renderer->addr + offset;
	*(unsigned int*)dst = color;
}

void  draw_floor_n_ceiling(t_engine *engine)
{
  int half_y;
  int y;
  int x;
  int color;

  half_y = engine->mlx->height / 2;
  y = 0;
  x = 0;
  while (y < engine->mlx->height)
  {
    x = 0;
    if (y < half_y)
      color = engine->map->c_color;
    else
      color = engine->map->f_color;
    while (x < engine->mlx->width)
    {
      put_pixel_to_image(engine->renderer, x, y, color);
      x++;
    }
    y++;
  }
}
