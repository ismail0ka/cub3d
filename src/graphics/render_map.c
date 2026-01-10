#include "cub3d.h"

void render_minimap(t_engine *engine, int tile_size) {
    int color;
    int x;
    int y;
  int tx;
    int ty;

    y = 0;
    while (y < engine->map->height) {
        x = 0;
        while (x < engine->map->width) {
            color = (engine->map->layout[y][x] == '1') ? 0xFFFFFF : 0x000000;
            ty = 0;
            while (ty < tile_size) {
                tx = 0;
                while (tx < tile_size) {
                    mlx_pixel_put(engine->mlx->mlx, engine->mlx->win, x * tile_size + tx, y * tile_size + ty, color);
                    tx++;
                }
                ty++;
            }
            x++;
        }
        y++;
    }
}
