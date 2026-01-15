/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 23:18:40 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/14 23:28:35 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_position_y(t_player *player, t_map *map, double next_y)
{
	if (is_position_valid(map, player->pos.x, next_y))
		player->pos.y = next_y;
}

void	update_position_x(t_player *player, t_map *map, double next_x)
{
	if (is_position_valid(map, next_x, player->pos.y))
		player->pos.x = next_x;
}
