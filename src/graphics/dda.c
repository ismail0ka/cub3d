/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:17:42 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/16 01:18:54 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	perform_dda_step(t_dda_data *dda, t_ray_data *rd)
{
	if (dda->side_dist_x < dda->side_dist_y)
	{
		dda->side_dist_x += dda->delta_dist_x;
		rd->map_x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_dist_y += dda->delta_dist_y;
		rd->map_y += dda->step_y;
		dda->side = 1;
	}
}

static int	check_hit(t_engine *e, t_ray_data *rd)
{
	if (rd->map_y < 0 || rd->map_y >= e->map->height)
		return (0);
	if (rd->map_x < 0)
		return (0);
	if ((size_t)rd->map_x >= ft_strlen(e->map->layout[rd->map_y]))
		return (0);
	if (e->map->layout[rd->map_y][rd->map_x] == '1')
		return (1);
	return (0);
}

void	run_dda(t_engine *e, t_ray_data *rd, t_dda_data *dda)
{
	int	max_steps;

	dda->hit = 0;
	max_steps = e->map->width * e->map->height + 64;
	while (!dda->hit && max_steps-- > 0)
	{
		if (rd->map_y < 0 || rd->map_y >= e->map->height)
			break ;
		if (rd->map_x < 0 || rd->map_x >= e->map->width)
			break ;
		perform_dda_step(dda, rd);
		if (check_hit(e, rd))
			dda->hit = 1;
	}
}
