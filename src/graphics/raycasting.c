/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:25:42 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 04:32:11 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include "cub3d.h"

static void	calculate_wall_x(t_raycast_result *res, t_engine *engine,
	double ray_dir_x, double ray_dir_y)
{
	double	wall_x;

	if (res->side == 0)
		wall_x = engine->player->pos.y + res->distance * ray_dir_y;
	else
		wall_x = engine->player->pos.x + res->distance * ray_dir_x;
	wall_x -= floor(wall_x);
	res->tex_x = wall_x;
}

static void	determine_texture_id(t_raycast_result *res, int step_x, int step_y)
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

static void	finalize_ray_result(t_raycast_result *res, t_dda_data *dda)
{
	if (dda->side == 0)
		res->distance = dda->side_dist_x - dda->delta_dist_x;
	else
		res->distance = dda->side_dist_y - dda->delta_dist_y;
	res->side = dda->side;
}

t_raycast_result	cast_ray(t_engine *e, int screen_x)
{
	t_raycast_result	res;
	t_ray_data			rd;
	t_dda_data			dda;

	res.distance = 1.0;
	res.tex_id = 0;
	res.tex_x = 0.0;
	res.side = 0;
	init_ray_data(&rd, e, screen_x);
	calc_delta_dist(&dda, &rd);
	init_step_x(&dda, &rd, e);
	init_step_y(&dda, &rd, e);
	run_dda(e, &rd, &dda);
	if (! dda.hit)
	{
		res.distance = 1e6;
		return (res);
	}
	finalize_ray_result(&res, &dda);
	calculate_wall_x(&res, e, rd.ray_dir_x, rd.ray_dir_y);
	determine_texture_id(&res, dda.step_x, dda.step_y);
	return (res);
}
