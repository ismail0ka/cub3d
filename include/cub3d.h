#ifndef CUB3D_H
#define CUB3D_H

#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mlx.h"
#include "../lib/libft/libft.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define TILE_SIZE 64
#define NUM_TEXTURES 4

#define KEY_W       13
#define KEY_A       0
#define KEY_S       1
#define KEY_D       2
#define KEY_LEFT    123
#define KEY_RIGHT   124
#define KEY_ESC     53

typedef struct s_position {
  double x;
  double y;
} t_position;

typedef struct s_mlx {
  void *mlx;
  void *win;
  int   width;
  int   height;
} t_mlx;

// Texture Structure for MiniLibX Images
typedef struct s_texture {
  void  *img;
  char  *addr;
  int   width;
  int   height;
  int   bpp;
  int   line_len;
  int   endian;
} t_texture;

typedef struct s_renderer {
  t_texture textures[NUM_TEXTURES];
  double    z_buffer[WIN_WIDTH];
} t_renderer;

// Map Representation
typedef struct s_map {
  char   **layout;
  char   *no_texture;
  char   *so_texture;
  char   *we_texture;
  char   *ea_texture;
  char   *floor_color;
  char   *ceiling_color;
  int     f_color;
  int     c_color;
  int     is_valid;
  int     height;
  int     width;
  double  player_x;
  double  player_y;
  double  player_angle;
} t_map;

typedef struct s_player {
  t_position pos;
  t_position direction;
  t_position plane;
  double     move_speed;
  double     rot_speed;
} t_player;

typedef struct s_engine {
  t_mlx      *mlx;
  t_renderer *renderer;
  t_map      *map;
  t_player   *player;
} t_engine;

// Stateless raycasting
// Instead of continually storing raycasting info in a struct compute it inside the rendering loop
typedef struct s_raycast_result {
  double distance;
  int    tex_id;
  double tex_x;
  int    side;
} t_raycast_result;

// Map Parsing
bool  parse_map(const char *file_path, t_map *map);

// Initialization
void  init_window(t_mlx *mlx, int width, int height, char *title);
void  init_player(t_player *player, const t_map *map);
void  init_renderer(t_renderer *renderer, t_mlx *mlx, t_map *map);

// Rendering & Raycasting
t_raycast_result cast_ray(t_engine *engine, int screen_x);
void  render_frame(t_engine *engine);  // Main rendering function

// Input Handling
int   handle_input(int keycode, t_engine *engine);
int   exit_game(t_engine *engine);
void  move_forward(t_player *player, char **map);
void  move_backward(t_player *player, char **layout);
void  strafe_left(t_player *player, char **layout);
void  strafe_right(t_player *player, char **layout);
void  rotate_left(t_player *player);
void  rotate_right(t_player *player);

// Cleanup & Exit
void  cleanup_engine(t_engine *engine);
void  exit_with_error(const char *error_message, t_engine *engine);

// Utility
int   rgb_to_hex(const char *rgb_str);  // Convert `R,G,B` string to hexadecimal
void  free_2d_array(char **arr);        // Free allocated 2D array (like `map.layout`)

// Rendering helpers
void  draw_floor_n_ceiling(t_engine *engine);
void  render_minimap(t_engine *engine, int tile_size);

#endif // CUB3D_H

