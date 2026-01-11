#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"
#include "parsing.h"

static double angle_for_char(char c)
{
  if (c == 'N')
    return -M_PI_2;
  if (c == 'S')
    return M_PI_2;
  if (c == 'E')
    return 0.0;
  return M_PI; // 'W'
}

static char **dup_map_lines(char **src, int *out_h, int *out_w)
{
  int   h;
  int   w;
  char **dst;
  int   i;

  if (!src)
    return NULL;
  h = 0;
  while (src[h])
    h++;
  w = (src[0]) ? (int)ft_strlen(src[0]) : 0;
  dst = calloc(h + 1, sizeof(char *));
  if (!dst)
    return NULL;
  i = 0;
  while (i < h)
  {
    dst[i] = malloc((size_t)w + 1);
    if (!dst[i])
      return NULL;
    // copy until w or string end (strings were normalized by parser)
    int j = 0;
    while (j < w && src[i][j])
    {
      dst[i][j] = src[i][j];
      j++;
    }
    while (j < w)
    {
      dst[i][j] = '1';
      j++;
    }
    dst[i][w] = '\0';
    i++;
  }
  dst[h] = NULL;
  if (out_h) *out_h = h;
  if (out_w) *out_w = w;
  return dst;
}

static char *make_rgb_str(int r, int g, int b)
{
  char *buf;
  // Max "255,255,255" length = 11 + null
  buf = malloc(16);
  if (!buf)
    return NULL;
  snprintf(buf, 16, "%d,%d,%d", r, g, b);
  return buf;
}

bool  parse_map(const char *file_path, t_map *map)
{
  t_params       *p;
  t_playerdata    player;
  t_raydata       ray;

  if (!file_path || !map)
    return false;
  memset(map, 0, sizeof(*map));

  p = params_holder();
  if (!p)
    return false;
  params_init(&p, &ray, &player);
  if (parse_args((char *)file_path) == -1)
    return false;

  // Textures
  map->no_texture = p->textures[NORTH_TEX] ? ft_strdup(p->textures[NORTH_TEX]) : NULL;
  map->so_texture = p->textures[SOUTH_TEX] ? ft_strdup(p->textures[SOUTH_TEX]) : NULL;
  map->we_texture = p->textures[WEST_TEX]  ? ft_strdup(p->textures[WEST_TEX])  : NULL;
  map->ea_texture = p->textures[EAST_TEX]  ? ft_strdup(p->textures[EAST_TEX])  : NULL;

  // Colors
  map->floor_color = make_rgb_str(p->floor_color[0], p->floor_color[1], p->floor_color[2]);
  map->ceiling_color = make_rgb_str(p->ceiling_color[0], p->ceiling_color[1], p->ceiling_color[2]);
  map->f_color = (p->floor_color[0] << 16) | (p->floor_color[1] << 8) | p->floor_color[2];
  map->c_color = (p->ceiling_color[0] << 16) | (p->ceiling_color[1] << 8) | p->ceiling_color[2];

  // Map layout
  map->layout = dup_map_lines(p->map, &map->height, &map->width);
  if (!map->layout)
    return false;

  // Player
  if (p->player && p->player->cell_x >= 0 && p->player->cell_y >= 0)
  {
    map->player_x = p->player->cell_x + 0.5;
    map->player_y = p->player->cell_y + 0.5;
    map->player_angle = angle_for_char(p->player->direction);
  }
  else
  {
    return false;
  }

  map->is_valid = 1;
  // Free parsing params but keep our copies
  free_params(&p);
  return true;
}
