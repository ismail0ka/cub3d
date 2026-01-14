/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:25:19 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/14 19:25:21 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void rotate_right(t_player *player) {
    double old_dir_x = player->direction.x;
    player->direction.x = cos(-player->rot_speed) * old_dir_x - sin(-player->rot_speed) * player->direction.y;
    player->direction.y = sin(-player->rot_speed) * old_dir_x + cos(-player->rot_speed) * player->direction.y;
    
    double old_plane_x = player->plane.x;
    player->plane.x = cos(-player->rot_speed) * old_plane_x - sin(-player->rot_speed) * player->plane.y;
    player->plane.y = sin(-player->rot_speed) * old_plane_x + cos(-player->rot_speed) * player->plane.y;
}

void rotate_left(t_player *player) {
    double old_dir_x = player->direction.x;
    player->direction.x = player->direction.x * cos(player->rot_speed)
                        - player->direction.y * sin(player->rot_speed);
    player->direction.y = old_dir_x * sin(player->rot_speed)
                        + player->direction.y * cos(player->rot_speed);

    double old_plane_x = player->plane.x;
    player->plane.x = player->plane.x * cos(player->rot_speed)
                    - player->plane.y * sin(player->rot_speed);
    player->plane.y = old_plane_x * sin(player->rot_speed)
                    + player->plane.y * cos(player->rot_speed);
}

/* Collision utils */
int is_position_valid(char **layout, int map_width, int map_height, double x, double y)
{
    int fx = floor(x);
    int fy = floor(y);
    double frac_x = x - fx;
    double frac_y = y - fy;

    if (fx < 0 || fy < 0 || fx >= map_width || fy >= map_height)
        return 0;
    if (!layout[fy] || (size_t)fx >= ft_strlen(layout[fy]))
        return 0;
    if (layout[fy][fx] == '1')
        return 0;
    if (frac_x < COLLISION_PAD && fx > 0 && layout[fy][fx - 1] == '1')
        return 0;
    if (frac_x > 1.0 - COLLISION_PAD && fx < map_width - 1 && layout[fy][fx + 1] == '1')
        return 0;
    if (frac_y < COLLISION_PAD && fy > 0 && layout[fy - 1][fx] == '1')
        return 0;
    if (frac_y > 1.0 - COLLISION_PAD && fy < map_height - 1 && layout[fy + 1][fx] == '1')
        return 0;
    return 1;
}

