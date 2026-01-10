#include "cub3d.h"

int handle_input(int keycode, t_engine *engine)
{
  t_player *player;

  player = engine->player;
  if (keycode == KEY_W)
      move_forward(player, engine->map->layout);
  else if (keycode == KEY_S)
      move_backward(player, engine->map->layout);
  else if (keycode == KEY_A)
      strafe_left(player, engine->map->layout);
  else if (keycode == KEY_D)
      strafe_right(player, engine->map->layout);
  else if (keycode == KEY_LEFT)
      rotate_left(player);
  else if (keycode == KEY_RIGHT)
      rotate_right(player);
  else if (keycode == KEY_ESC)
      exit_game(engine);
  return 0;
}

void exit_game(t_engine *engine) {
    cleanup_engine(engine);
    exit(0);
}
