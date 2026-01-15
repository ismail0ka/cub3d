/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:25:11 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/14 23:24:01 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_player *player, t_map *map)
{
	double	next_x;
	double	next_y;

	next_x = player->pos.x + player->direction. x * player->move_speed;
	next_y = player->pos.y + player->direction. y * player->move_speed;
	update_position_y(player, map, next_y);
	update_position_x(player, map, next_x);
}

void	move_backward(t_player *player, t_map *map)
{
	double	next_x;
	double	next_y;

	next_x = player->pos. x - player->direction.x * player->move_speed;
	next_y = player->pos. y - player->direction.y * player->move_speed;
	update_position_y(player, map, next_y);
	update_position_x(player, map, next_x);
}

void	strafe_left(t_player *player, t_map *map)
{
	double	next_x;
	double	next_y;

	next_x = player->pos. x - player->plane.x * player->move_speed;
	next_y = player->pos. y - player->plane.y * player->move_speed;
	update_position_y(player, map, next_y);
	update_position_x(player, map, next_x);
}

void	strafe_right(t_player *player, t_map *map)
{
	double	next_x;
	double	next_y;

	next_x = player->pos. x + player->plane.x * player->move_speed;
	next_y = player->pos. y + player->plane.y * player->move_speed;
	update_position_y(player, map, next_y);
	update_position_x(player, map, next_x);
}
