#include "cub3d.h"

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
      mlx_pixel_put(engine->mlx->mlx, engine->mlx->win, x, y, color);
      x++;
    }
    y++;
  }
}
