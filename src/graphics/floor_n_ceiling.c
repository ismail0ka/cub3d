/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_n_ceiling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:25:25 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 04:17:06 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_image(t_renderer *renderer, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (!renderer || !renderer->addr || x < 0 || y < 0)
		return ;
	offset = y * renderer->line_len + x * (renderer->bpp / 8);
	dst = renderer->addr + offset;
	*(unsigned int *) dst = color;
}

static int	get_color(t_engine *engine, int y, int half_y)
{
	if (y < half_y)
		return (engine->map->c_color);
	else
		return (engine->map->f_color);
}

void	draw_floor_n_ceiling(t_engine *engine)
{
	int	half_y;
	int	y;
	int	x;
	int	color;

	half_y = engine->mlx->height / 2;
	y = 0;
	while (y < engine->mlx->height)
	{
		x = 0;
		color = get_color(engine, y, half_y);
		while (x < engine->mlx->width)
		{
			put_pixel_to_image(engine->renderer, x, y, color);
			x++;
		}
		y++;
	}
}
