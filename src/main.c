#include "cub3d.h"

static void print_usage(void)
{
  printf("Usage: ./cub3d <scene_description.cub>\n\n");
  printf("Controls:\n");
  printf("  - W, A, S, D: Move the player\n");
  printf("  - Arrow Keys: Rotate the view\n");
  printf("  - ESC: Exit the program\n");
}

void  init_window(t_mlx *mlx, int width, int height, char *title)
{
  mlx->mlx = mlx_init();
  if (!mlx->mlx)
    (perror("Failed to init mlx"), exit(EXIT_FAILURE));
  mlx->width = width;
  mlx->height = height;
  mlx->win = mlx_new_window(mlx->mlx, width, height, title);
  if (!mlx->win)
    (perror("Failed to init mlx window"), exit(EXIT_FAILURE));
}

int main(int argc, char **argv)
{
  t_engine  engine;

  ft_memset(&engine, 0, sizeof(engine));
  engine.mlx = ft_calloc(1, sizeof(t_mlx));
  engine.renderer = ft_calloc(1, sizeof(t_renderer));
  engine.map = ft_calloc(1, sizeof(t_map));
  engine.player = ft_calloc(1, sizeof(t_player));
  if (!engine.mlx || !engine.renderer || !engine.map || !engine.player)
    exit_with_error("Memory allocation failed", &engine);
  if (argc != 2)
  {
    print_usage();
    cleanup_engine(&engine);
    return EXIT_FAILURE;
  }
  if (!parse_map(argv[1], engine.map))
    exit_with_error("Failed to parse map", &engine);

  init_window(engine.mlx, WIN_WIDTH, WIN_HEIGHT, "Gangsta3D");
  init_player(engine.player, engine.map);
  init_renderer(engine.renderer, engine.mlx, engine.map);

  render_frame(&engine);
  mlx_hook(engine.mlx->win, 2, 1L << 0, handle_input, &engine);
  mlx_hook(engine.mlx->win, 17, 0, exit_game, &engine);
  mlx_loop(engine.mlx->mlx);

  cleanup_engine(&engine);
  return EXIT_SUCCESS;
}
