/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:13:14 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 04:19:39 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_data(t_ray_data *rd, t_engine *e, int screen_x)
{
	rd->camera_x = 2.0 * screen_x / (double)e->mlx->width - 1.0;
	rd->ray_dir_x = e->player->direction. x;
	rd->ray_dir_x += e->player->plane.x * rd->camera_x;
	rd->ray_dir_y = e->player->direction.y;
	rd->ray_dir_y += e->player->plane. y * rd->camera_x;
	rd->map_x = (int)e->player->pos.x;
	rd->map_y = (int)e->player->pos.y;
}

void	calc_delta_dist(t_dda_data *dda, t_ray_data *rd)
{
	if (rd->ray_dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1.0 / rd->ray_dir_x);
	if (rd->ray_dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1.0 / rd->ray_dir_y);
}

void	init_step_x(t_dda_data *dda, t_ray_data *rd, t_engine *e)
{
	if (rd->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (e->player->pos.x - rd->map_x);
		dda->side_dist_x *= dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (rd->map_x + 1.0 - e->player->pos.x);
		dda->side_dist_x *= dda->delta_dist_x;
	}
}

void	init_step_y(t_dda_data *dda, t_ray_data *rd, t_engine *e)
{
	if (rd->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (e->player->pos.y - rd->map_y);
		dda->side_dist_y *= dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (rd->map_y + 1.0 - e->player->pos.y);
		dda->side_dist_y *= dda->delta_dist_y;
	}
}
