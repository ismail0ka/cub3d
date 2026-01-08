#include "cub3d.h"

void render_minimap(t_engine *engine, int tile_size) {
    int color;
    int x;
    int y;
    int ty;

    x = 0;
    y = 0;
    tx = 0;
    ty = 0;
    while (y < engine->map->height) {
        while (x < engine->map->width) {
            if (engine->map->layout[y][x] == '1')
              color = 0xFFFFFF;
            else
              color = 0x000000;
            while (ty < tile_size) {
                while (tx < tile_size) {
                    mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x * tile_size + tx, y * tile_size + ty, color);
                    tx++;
                }
              ty++;
            }
          x++;
        }
      y++;
    }
}
