/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:24:57 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/14 19:24:59 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int handle_input(int keycode, t_engine *engine)
{
  t_player *player;

  player = engine->player;
  if (keycode == KEY_ESC)
      exit_game(engine);
  if (keycode == KEY_W)
      move_forward(player, engine->map);
  else if (keycode == KEY_S)
      move_backward(player, engine->map);
  else if (keycode == KEY_A)
      strafe_left(player, engine->map);
  else if (keycode == KEY_D)
      strafe_right(player, engine->map);
  else if (keycode == KEY_LEFT)
      rotate_left(player);
  else if (keycode == KEY_RIGHT)
      rotate_right(player);
  render_frame(engine);
  return 0;
}

int exit_game(t_engine *engine) {
    cleanup_engine(engine);
    exit(0);
    return (0);
}
