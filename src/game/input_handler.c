/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:24:57 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/14 20:26:53 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement(int keycode, t_player *player, t_map *map)
{
	if (keycode == KEY_W)
		move_forward(player, map);
	else if (keycode == KEY_S)
		move_backward(player, map);
	else if (keycode == KEY_A)
		strafe_left(player, map);
	else if (keycode == KEY_D)
		strafe_right(player, map);
}

static void	handle_rotation(int keycode, t_player *player)
{
	if (keycode == KEY_LEFT)
		rotate_left(player);
	else if (keycode == KEY_RIGHT)
		rotate_right(player);
}

int	handle_input(int keycode, t_engine *engine)
{
	t_player	*player;

	player = engine->player;
	if (keycode == KEY_ESC)
		exit_game(engine);
	handle_movement(keycode, player, engine->map);
	handle_rotation(keycode, player);
	render_frame(engine);
	return (0);
}

int	exit_game(t_engine *engine)
{
	cleanup_engine(engine);
	exit(0);
	return (0);
}
