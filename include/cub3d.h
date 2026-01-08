#ifndef CUB3D_H
#define CUB3D_H

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define TILE_SIZE 64          // Standard size for map tiles
#define NUM_TEXTURES 4

# include <math.h>
# include "mlx.h"

// Map Representation
typedef struct s_map {
    char    **layout;        // 2D map grid of the game (walls, player pos, etc.)
    char    *no_texture;     // North Wall Texture Path
    char    *so_texture;     // South Wall Texture Path
    char    *we_texture;     // West Wall Texture Path
    char    *ea_texture;     // East Wall Texture Path
    char    *floor_color;    // Floor RGB color (parsed as string then converted)
    char    *ceiling_color;  // Ceiling RGB color (parsed as string then converted)
    int     is_valid;        // 1 if parsed correctly, 0 otherwise
    int     map_height;      // Number of rows in the map
    int     map_width;       // Longest row in the map
    double  player_x;        // Starting player X pos
    double  player_y;        // Starting player Y pos
    double  player_angle;    // Starting angle/direction for the player
} t_map;

// Player's Position & Movement Logic
typedef struct s_player {
    t_position pos;          // (X, Y) position of the player
    t_position direction;    // Direction vector (dir_x, dir_y)
    t_position plane;        // Camera plane vector
    double     move_speed;   // Speed of movement per frame
    double     rot_speed;    // Speed of rotation per frame
} t_player;

// Game Engine (Main Aggregating Struct)
typedef struct s_engine {
    t_mlx        mlx;        // MiniLibX state
    t_renderer   renderer;   // Rendering data
    t_map        map;        // Map data
    t_player     player;     // Player state
} t_engine;

//Window
typedef struct s_mlx {
  void  *mlx;
  void  *win;
  int   width;
  int   height;
} t_mlx;

// Texture Structure for MiniLibX Images
typedef struct s_texture {
    void    *img;          // Pointer to the MiniLibX image object
    char    *addr;         // Pointer to the image's pixel data
    int     width;         // Texture width in pixels
    int     height;        // Texture height in pixels
    int     bpp;           // Bits per pixel (e.g., 32 for RGBA)
    int     line_len;      // Number of bytes in a row of the image
    int     endian;        // Endian format of the image (0 = little, 1 = big)
} t_texture;

//Renderer
typedef struct s_renderer {
  t_texture textures[NUM_TEXTURES];
  double    z_buffer[MAX_WIDTH];
} t_renderer;

//Player
typedef struct s_player {
  t_position  pos;
  t_position  dir;
  t_position  plane;
  double      mov_speed;
  double      rot_speed;
} t_player;

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

// Map Parsing
bool        parse_map(const char *file_path, t_map *map);

// Initialization
void        init_window(t_mlx *mlx, int width, int height, const char *title);
void        init_player(t_player *player, const t_map *map);
void        init_renderer(t_renderer *renderer, t_mlx *mlx, t_map *map);

// Rendering & Raycasting
t_raycast_result cast_ray(t_engine *engine, int screen_x);
void        render_frame(t_engine *engine);  // Main rendering function

// Input Handling
int         handle_input(int keycode, t_engine *engine);

// Cleanup & Exit
void        cleanup_engine(t_engine *engine);
void        exit_with_error(const char *error_message, t_engine *engine);

// Utility
int         rgb_to_hex(const char *rgb_str);  // Convert `R,G,B` string to hexadecimal
void        free_2d_array(char **arr);       // Free allocated 2D array (like `map.layout`)

#endif //CUB3D_H

