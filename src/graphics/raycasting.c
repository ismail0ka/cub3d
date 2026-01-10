#include <math.h>
#include <stddef.h>
#include "cub3d.h"

static void draw_vertical_line(t_engine *engine, int x, int start, int end, int color)
{
	int y;

	if (!engine || !engine->mlx)
		return;
	if (start < 0)
		start = 0;
	if (end >= engine->mlx->height)
		end = engine->mlx->height - 1;
	y = start;
	while (y <= end)
	{
		mlx_pixel_put(engine->mlx->mlx, engine->mlx->win, x, y, color);
		y++;
	}
}

t_raycast_result cast_ray(t_engine *engine, int screen_x)
{
	t_raycast_result res;
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int    map_x;
	int    map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	int    step_x;
	int    step_y;
	int    hit;
	int    side;

	res.distance = 1.0;
	res.tex_id = 0;
	res.tex_x = 0.0;
	res.side = 0;
	camera_x = 2.0 * screen_x / (double)engine->mlx->width - 1.0;
	ray_dir_x = engine->player->direction.x + engine->player->plane.x * camera_x;
	ray_dir_y = engine->player->direction.y + engine->player->plane.y * camera_x;
	map_x = (int)engine->player->pos.x;
	map_y = (int)engine->player->pos.y;
	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (engine->player->pos.x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - engine->player->pos.x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (engine->player->pos.y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - engine->player->pos.y) * delta_dist_y;
	}
	hit = 0;
	side = 0;
	int max_steps = engine->map->width * engine->map->height + 64;
	while (!hit && max_steps-- > 0 && map_y >= 0 && map_y < engine->map->height && map_x >= 0 && map_x < engine->map->width)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (map_y >= 0 && map_y < engine->map->height &&
				map_x >= 0 && map_x < engine->map->width &&
				engine->map->layout[map_y][map_x] == '1')
			hit = 1;
	}
	if (!hit)
	{
		res.distance = 1e6; /* treat as very far to avoid div-by-zero */
		return res;
	}
	if (side == 0)
		res.distance = side_dist_x - delta_dist_x;
	else
		res.distance = side_dist_y - delta_dist_y;
	res.side = side;
	/* Minimal texture coordinate placeholder */
	res.tex_x = 0.0;
	res.tex_id = 0;
	return res;
}

void  render_frame(t_engine *engine)
{
	int               x;
	t_raycast_result  ray;
	int               line_height;
	int               draw_start;
	int               draw_end;
	double            dist;
	int               color;

	if (!engine || !engine->mlx)
		return;
	draw_floor_n_ceiling(engine);
	x = 0;
	while (x < engine->mlx->width)
	{
		ray = cast_ray(engine, x);
		dist = (ray.distance <= 0.0001) ? 0.0001 : ray.distance;
		engine->renderer->z_buffer[x] = dist;
		line_height = (int)(engine->mlx->height / dist);
		draw_start = -line_height / 2 + engine->mlx->height / 2;
		draw_end = line_height / 2 + engine->mlx->height / 2;
		color = (ray.side) ? 0xAAAAAA : 0xFFFFFF;
		draw_vertical_line(engine, x, draw_start, draw_end, color);
		x++;
	}
}
