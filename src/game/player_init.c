/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:25:03 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/14 19:25:06 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_player *player, const t_map *map)
{
    double angle;

    if (!player || !map)
        return;
    angle = map->player_angle;
    player->pos.x = map->player_x;
    player->pos.y = map->player_y;
    player->direction.x = cos(angle);
    player->direction.y = sin(angle);
    player->plane.x = -player->direction.y * 0.66;
    player->plane.y = player->direction.x * 0.66;
    player->move_speed = 0.1;
    player->rot_speed = 0.05;
}
