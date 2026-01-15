/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:50:54 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 16:13:09 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_fallback_wall(t_engine *e, t_wall_draw *wd)
{
	int	y;
	int	color;

	y = wd->start;
	if (wd->ray.side)
		color = 0x808080;
	else
		color = 0xFFFFFF;
	while (y <= wd->end)
	{
		put_pixel_to_image(e->renderer, wd->x, y, color);
		y++;
	}
}

static int	get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*dst;
	int		offset;

	if (!tex || !tex->addr || x < 0 || y < 0
		|| x >= tex->width || y >= tex->height)
		return (0);
	offset = y * tex->line_len + x * (tex->bpp / 8);
	dst = tex->addr + offset;
	return (*(unsigned int *)dst);
}

static void	render_textured_column(t_engine *e, t_texture *tex,
			t_wall_draw *wd)
{
	int		tex_x;
	int		tex_y;
	int		y;
	int		color;
	double	pos;

	tex_x = (int)(wd->ray.tex_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	pos = (wd->start - e->mlx->height / 2 + (wd->end - wd->start) / 2);
	pos *= 1.0 * tex->height / (wd->end - wd->start);
	y = wd->start;
	while (y <= wd->end)
	{
		tex_y = (int)pos & (tex->height - 1);
		pos += 1.0 * tex->height / (wd->end - wd->start);
		color = get_texture_pixel(tex, tex_x, tex_y);
		if (wd->ray.side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel_to_image(e->renderer, wd->x, y, color);
		y++;
	}
}

void	draw_textured_wall(t_engine *e, t_wall_draw *wd)
{
	t_texture	*tex;

	if (wd->ray.tex_id < 0 || wd->ray.tex_id >= NUM_TEXTURES)
		return ;
	tex = &e->renderer->textures[wd->ray.tex_id];
	if (! tex->img || !tex->addr)
	{
		draw_fallback_wall(e, wd);
		return ;
	}
	render_textured_column(e, tex, wd);
}
