/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:24:23 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 04:45:43 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "mlx.h"
# include "../lib/libft/libft.h"

# define WIN_WIDTH 908
# define WIN_HEIGHT 640
# define TILE_SIZE 64
# define NUM_TEXTURES 4

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65363
# define KEY_RIGHT 65361
# define KEY_ESC 65307

# define COLLISION_PAD 0.4

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_renderer
{
	t_texture	textures[NUM_TEXTURES];
	double		z_buffer[WIN_WIDTH];
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_renderer;

typedef struct s_map
{
	char	**layout;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		f_color;
	int		c_color;
	int		is_valid;
	int		height;
	int		width;
	double	player_x;
	double	player_y;
	double	player_angle;
}	t_map;

typedef struct s_player
{
	t_position	pos;
	t_position	direction;
	t_position	plane;
	double		move_speed;
	double		rot_speed;
}	t_player;

typedef struct s_engine
{
	t_mlx		*mlx;
	t_renderer	*renderer;
	t_map		*map;
	t_player	*player;
}	t_engine;

typedef struct s_raycast_result
{
	double	distance;
	int		tex_id;
	double	tex_x;
	int		side;
}	t_raycast_result;

typedef struct s_ray_data
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
}	t_ray_data;

typedef struct s_dda_data
{
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_dda_data;

typedef struct s_wall_draw
{
	int					x;
	int					start;
	int					end;
	t_raycast_result	ray;
}	t_wall_draw;

int					parse_map(const char *file_path, t_map *map);
void				init_window(t_mlx *mlx, int width, int height, char *title);
void				init_player(t_player *player, const t_map *map);
void				init_renderer(t_renderer *renderer, t_mlx *mlx, t_map *map);
t_raycast_result	cast_ray(t_engine *engine, int screen_x);
void				draw_textured_wall(t_engine *e, int x, int start,
						int end, t_raycast_result ray);
void				render_frame(t_engine *engine);
void				draw_floor_n_ceiling(t_engine *engine);
int					is_position_valid(t_map *map, double x, double y);
void				render_minimap(t_engine *engine, int tile_size);
void				init_ray_data(t_ray_data *rd, t_engine *e, int screen_x);
void				calc_delta_dist(t_dda_data *dda, t_ray_data *rd);
void				init_step_x(t_dda_data *dda, t_ray_data *rd, t_engine *e);
void				init_step_y(t_dda_data *dda, t_ray_data *rd, t_engine *e);
void				run_dda(t_engine *e, t_ray_data *rd, t_dda_data *dda);
void				put_pixel_to_image(t_renderer *r, int x, int y, int color);
int					handle_input(int keycode, t_engine *engine);
int					exit_game(t_engine *engine);
void				move_forward(t_player *player, t_map *map);
void				move_backward(t_player *player, t_map *map);
void				strafe_left(t_player *player, t_map *map);
void				strafe_right(t_player *player, t_map *map);
void				rotate_left(t_player *player);
void				rotate_right(t_player *player);
void				update_position_y(t_player *player, t_map *map,
						double next_y);
void				update_position_x(t_player *player, t_map *map,
						double next_x);
double				angle_for_char(char c);
char				**alloc_map_lines(char **src, int h, int w);
char				**dup_map_lines(char **src, int *out_h, int *out_w);
void				cleanup_engine(t_engine *engine);
void				exit_with_error(const char *error_message,
						t_engine *engine);
void				free_2d_array(char **arr);

#endif
