#include <math.h>
#include <stddef.h>
#include "cub3d.h"

static void put_pixel_to_image(t_renderer *renderer, int x, int y, int color)
{
	char *dst;
	int offset;

	if (!renderer || !renderer->addr || x < 0 || y < 0)
		return;
	offset = y * renderer->line_len + x * (renderer->bpp / 8);
	dst = renderer->addr + offset;
	*(unsigned int*)dst = color;
}

static int get_texture_pixel(t_texture *tex, int x, int y)
{
	char *dst;
	int offset;

	if (!tex || !tex->addr || x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return 0;
	offset = y * tex->line_len + x * (tex->bpp / 8);
	dst = tex->addr + offset;
	return *(unsigned int*)dst;
}

static void calculate_wall_x(t_raycast_result *res, t_engine *engine, double ray_dir_x, double ray_dir_y)
{
	double wall_x;

	if (res->side == 0)
		wall_x = engine->player->pos.y + res->distance * ray_dir_y;
	else
		wall_x = engine->player->pos.x + res->distance * ray_dir_x;
	wall_x -= floor(wall_x);
	res->tex_x = wall_x;
}

static void determine_texture_id(t_raycast_result *res, int step_x, int step_y)
{
	if (res->side == 0)
	{
		if (step_x > 0)
			res->tex_id = 3;
		else
			res->tex_id = 2;
	}
	else
	{
		if (step_y > 0)
			res->tex_id = 1;
		else
			res->tex_id = 0;
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
		res.distance = 1e6;
		return res;
	}
	if (side == 0)
		res.distance = side_dist_x - delta_dist_x;
	else
		res.distance = side_dist_y - delta_dist_y;
	res.side = side;
	calculate_wall_x(&res, engine, ray_dir_x, ray_dir_y);
	determine_texture_id(&res, step_x, step_y);
	return res;
}

static void draw_textured_wall(t_engine *engine, int x, int draw_start, int draw_end, t_raycast_result ray)
{
	t_texture *texture;
	int tex_x;
	int tex_y;
	double step;
	double tex_pos;
	int y;
	int color;

	if (ray.tex_id < 0 || ray.tex_id >= NUM_TEXTURES)
		return;
	texture = &engine->renderer->textures[ray.tex_id];
	if (!texture->img || !texture->addr)
	{
		y = draw_start;
		while (y <= draw_end)
		{
			put_pixel_to_image(engine->renderer, x, y, (ray.side) ? 0x808080 : 0xFFFFFF);
			y++;
		}
		return;
	}
	tex_x = (int)(ray.tex_x * (double)texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	step = 1.0 * texture->height / (draw_end - draw_start);
	tex_pos = (draw_start - engine->mlx->height / 2 + (draw_end - draw_start) / 2) * step;
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = get_texture_pixel(texture, tex_x, tex_y);
		if (ray.side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel_to_image(engine->renderer, x, y, color);
		y++;
	}
}

void  render_frame(t_engine *engine)
{
	int               x;
	t_raycast_result  ray;
	int               line_height;
	int               draw_start;
	int               draw_end;
	double            dist;

	if (!engine || !engine->mlx || !engine->renderer)
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
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= engine->mlx->height)
			draw_end = engine->mlx->height - 1;
		draw_textured_wall(engine, x, draw_start, draw_end, ray);
		x++;
	}
	mlx_put_image_to_window(engine->mlx->mlx, engine->mlx->win, engine->renderer->img, 0, 0);
}
