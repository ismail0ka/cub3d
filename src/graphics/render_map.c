/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:25:47 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 20:23:29 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_draw_bounds(int *start, int *end, int line_h, int screen_h)
{
	*start = -line_h / 2 + screen_h / 2;
	*end = line_h / 2 + screen_h / 2;
	if (*start < 0)
		*start = 0;
	if (*end >= screen_h)
		*end = screen_h - 1;
}

static void	render_column(t_engine *e, int x)
{
	t_wall_draw			wd;
	int					line_height;
	double				dist;

	wd.ray = cast_ray(e, x);
	dist = wd.ray.distance;
	if (dist <= 0.0001)
		dist = 0.0001;
	e->renderer->z_buffer[x] = dist;
	line_height = (int)(e->mlx->height / dist);
	wd.x = x;
	calc_draw_bounds(&wd.start, &wd.end, line_height, e->mlx->height);
	draw_textured_wall(e, &wd);
}

void	render_frame(t_engine *e)
{
	int	x;

	if (!e || !e->mlx || !e->renderer)
		return ;
	draw_floor_n_ceiling(e);
	x = 0;
	while (x < e->mlx->width)
	{
		render_column(e, x);
		x++;
	}
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win,
		e->renderer->img, 0, 0);
}

static int	get_tile_color(char tile)
{
	if (tile == '1')
		return (0xFFFFFF);
	return (0x000000);
}

void	render_minimap(t_engine *e, int tile_size)
{
	int	x;
	int	y;
	int	tx;
	int	ty;
	int	color;

	y = -1;
	while (++y < e->map->height)
	{
		x = -1;
		while (++x < e->map->width)
		{
			color = get_tile_color(e->map->layout[y][x]);
			ty = -1;
			while (++ty < tile_size)
			{
				tx = -1;
				while (++tx < tile_size)
					mlx_pixel_put(e->mlx->mlx, e->mlx->win,
						x * tile_size + tx, y * tile_size + ty, color);
			}
		}
	}
}
