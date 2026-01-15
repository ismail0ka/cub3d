/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 23:23:08 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 19:48:03 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_bounds(t_map *map, int fx, int fy)
{
	if (fx < 0 || fy < 0 || fx >= map->width || fy >= map->height)
		return (0);
	if (!map->layout[fy] || (size_t)fx >= ft_strlen(map->layout[fy]))
		return (0);
	if (map->layout[fy][fx] == '1')
		return (0);
	return (1);
}

static int	check_x_collision(char **layout, int fx, int fy, double frac_x)
{
	if (frac_x < COLLISION_PAD && fx > 0)
	{
		if (layout[fy][fx - 1] == '1')
			return (0);
	}
	if (frac_x > 1.0 - COLLISION_PAD)
	{
		if (layout[fy][fx + 1] == '1')
			return (0);
	}
	return (1);
}

static int	check_y_collision(char **layout, int fx, int fy, double frac_y)
{
	if (frac_y < COLLISION_PAD && fy > 0)
	{
		if (layout[fy - 1][fx] == '1')
			return (0);
	}
	if (frac_y > 1.0 - COLLISION_PAD)
	{
		if (layout[fy + 1][fx] == '1')
			return (0);
	}
	return (1);
}

int	is_position_valid(t_map *map, double x, double y)
{
	int		fx;
	int		fy;
	double	frac_x;
	double	frac_y;

	fx = floor(x);
	fy = floor(y);
	frac_x = x - fx;
	frac_y = y - fy;
	if (! check_bounds(map, fx, fy))
		return (0);
	if (!check_x_collision(map->layout, fx, fy, frac_x))
		return (0);
	if (!check_y_collision(map->layout, fx, fy, frac_y))
		return (0);
	return (1);
}
