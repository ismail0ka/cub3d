/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:25:19 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/14 23:23:44 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_direction(t_player *player, double angle)
{
	double	old_dir_x;
	double	cos_a;
	double	sin_a;

	old_dir_x = player->direction.x;
	cos_a = cos(angle);
	sin_a = sin(angle);
	player->direction.x = cos_a * old_dir_x - sin_a * player->direction.y;
	player->direction.y = sin_a * old_dir_x + cos_a * player->direction.y;
}

static void	rotate_plane(t_player *player, double angle)
{
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	old_plane_x = player->plane.x;
	cos_a = cos(angle);
	sin_a = sin(angle);
	player->plane.x = cos_a * old_plane_x - sin_a * player->plane.y;
	player->plane.y = sin_a * old_plane_x + cos_a * player->plane.y;
}

void	rotate_right(t_player *player)
{
	rotate_direction(player, -player->rot_speed);
	rotate_plane(player, -player->rot_speed);
}

void	rotate_left(t_player *player)
{
	rotate_direction(player, player->rot_speed);
	rotate_plane(player, player->rot_speed);
}
