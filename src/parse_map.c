/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:26:10 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 04:44:00 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"
#include "parsing.h"

static int	assign_textures(t_map *map, t_params *p)
{
	if (p->textures[NORTH_TEX])
		map->no_texture = ft_strdup(p->textures[NORTH_TEX]);
	else
		map->no_texture = NULL;
	if (p->textures[SOUTH_TEX])
		map->so_texture = ft_strdup(p->textures[SOUTH_TEX]);
	else
		map->so_texture = NULL;
	if (p->textures[WEST_TEX])
		map->we_texture = ft_strdup(p->textures[WEST_TEX]);
	else
		map->we_texture = NULL;
	if (p->textures[EAST_TEX])
		map->ea_texture = ft_strdup(p->textures[EAST_TEX]);
	else
		map->ea_texture = NULL;
	return (1);
}

static void	assign_colors(t_map *map, t_params *p)
{
	map->f_color = (p->floor_color[0] << 16);
	map->f_color |= (p->floor_color[1] << 8);
	map->f_color |= p->floor_color[2];
	map->c_color = (p->ceiling_color[0] << 16);
	map->c_color |= (p->ceiling_color[1] << 8);
	map->c_color |= p->ceiling_color[2];
}

static int	assign_player(t_map *map, t_params *p)
{
	if (! p->player)
		return (0);
	if (p->player->cell_x < 0 || p->player->cell_y < 0)
		return (0);
	map->player_x = p->player->cell_x + 0.5;
	map->player_y = p->player->cell_y + 0.5;
	map->player_angle = angle_for_char(p->player->direction);
	return (1);
}

static int	init_parsing(t_params **p, t_playerdata *player, t_raydata *ray)
{
	*p = params_holder();
	if (!*p)
		return (0);
	params_init(p, ray, player);
	return (1);
}

int	parse_map(const char *file_path, t_map *map)
{
	t_params		*p;
	t_playerdata	player;
	t_raydata		ray;

	if (!file_path || !map)
		return (0);
	ft_memset(map, 0, sizeof(*map));
	if (!init_parsing(&p, &player, &ray))
		return (0);
	if (parse_args((char *)file_path) == -1)
		return (0);
	if (!assign_textures(map, p))
		return (0);
	assign_colors(map, p);
	map->layout = dup_map_lines(p->map, &map->height, &map->width);
	if (!map->layout)
		return (0);
	if (!assign_player(map, p))
		return (0);
	map->is_valid = 1;
	free_params(&p);
	return (1);
}
