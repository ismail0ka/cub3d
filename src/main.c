#include "cub3d.h"

char map[24][25] = {
    "111111111111111111111111",
    "100000000000000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "100001111110000101010001",
    "100001000010000000000001",
    "100001000010000100010001",
    "100001000010000000000001",
    "100001110110000101010001",
    "100000000N00000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "111111111100000000000001",
    "110100000100000000000001",
    "110000001100000000000001",
    "110100000100000000000001",
    "111111111100000000000001",
    "110000000000000000000001",
    "111111111100000000000001",
    "111111111111111111111111"
};

void  print_usage()
{
  printf("Usage: ./cub3d <scene_description.cub>\n");
  printf("\n");
  printf("Description:\n");
  printf("  Our Poorly replicated Wolfenstein 3D.\n");
  printf("\n");
  printf("Controls:\n");
  printf("  - W, A, S, D: Move the player\n");
  printf("  - Arrow Keys: Rotate the view\n");
  printf("  - ESC: Exit the program\n");
  exit(EXIT_FAILURE);
}

void  init_window(t_mlx *mlx, int width, int height, char *title)
{
  mlx->mlx = mlx_init();
  if (!mlx->mlx)
    (perror("Failed to init mlx.\n"), exit(EXIT_FAILURE));
  mlx->width = width;
  mlx->height = height;
  mlx->win = mlx_new_window(mlx, width, height, title);
  if (!mlx->win)
    (perror("Failed to init mlx window.\n"), exit(EXIT_FAILURE));
}

int main(int argc, char **argv) {
  t_engine *engine;

  if (argc == 2 && init_game(engine))
  {
    init_window(&mlx, WIN_WIDTH, WIN_HEIGHT, "Gangsta3D");
    mlx_hook(engine->mlx, 2, 1L << 0, handle_input, &engine);
    mlx_loop(engine->mlx->mlx);
  }
  else
    print_usage();
  return 0;
}
