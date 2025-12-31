#ifndef CUB3D_H
#define CUB3D_H

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

# include <math.h>

//Game state
typedef struct s_game_state {
  t_map     map;
  t_player  player;
  t_sprite  *sprites;
} t_game_state;

//Renderer
typedef struct s_renderer {
  t_texture textures[NUM_TEXTURES];
  double    z_buffer[MAX_WIDTH];
  t_img     screen;
} t_renderer;

//Win
typedef struct s_window {
  void  *mlx;
  void  *win;
  int   width;
  int   height;
} t_window;

//Player
typedef struct s_player {
  t_pos pos;
  t_pos dir;
  t_pos plane;
  double  mov_speed;
  double  rot_speed;
} t_player;

//The engine
typedef struct s_engine {
  t_window      win;
  t_renderer    renderer;
  t_game_state  game_state;
} t_engine;

typedef struct s_position {
  double  x;
  double  y;
} t_position;

//Stateless raycasting
//Instead of continually storing raycasting info in a struct compute it inside the rendering loop
typedef struct s_raycast_result {
  double  distance;
  int     tex_id;
  double  tex_x;
  int     side;
} t_raycast_result;

t_raycast_result  cast_ray(t_engine *e, int x);

#endif //CUB3D_H
