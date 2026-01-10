#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cub3d.h"

static void free_lines(char **lines, int count)
{
  int i;

  if (!lines)
    return;
  i = 0;
  while (i < count)
  {
    free(lines[i]);
    i++;
  }
  free(lines);
}

static int is_player_char(char c)
{
  return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

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

static int build_layout(t_map *map, char **lines, int line_count, int max_width)
{
  int y;
  int x;

  map->layout = calloc(line_count + 1, sizeof(char *));
  if (!map->layout)
    return 0;
  map->height = line_count;
  map->width = max_width;
  y = 0;
  while (y < line_count)
  {
    map->layout[y] = calloc(max_width + 1, sizeof(char));
    if (!map->layout[y])
      return 0;
    x = 0;
    while (x < max_width)
    {
      if ((int)strlen(lines[y]) > x)
        map->layout[y][x] = lines[y][x];
      else
        map->layout[y][x] = '1';
      x++;
    }
    map->layout[y][max_width] = '\0';
    y++;
  }
  map->layout[line_count] = NULL;
  return 1;
}

bool  parse_map(const char *file_path, t_map *map)
{
  FILE   *fp;
  char   *line;
  size_t  len;
  ssize_t nread;
  char  **lines;
  int     capacity;
  int     count;
  int     max_width;
  int     player_found;
  int     i;

  if (!file_path || !map)
    return false;
  memset(map, 0, sizeof(*map));
  map->f_color = 0x444444;
  map->c_color = 0x87CEEB;
  fp = fopen(file_path, "r");
  if (!fp)
    return false;
  line = NULL;
  len = 0;
  lines = NULL;
  capacity = 0;
  count = 0;
  max_width = 0;
  player_found = 0;
  while ((nread = getline(&line, &len, fp)) != -1)
  {
    while (nread > 0 && (line[nread - 1] == '\n' || line[nread - 1] == '\r'))
      line[--nread] = '\0';
    if (nread == 0)
      continue;
    if (count >= capacity)
    {
      capacity = (capacity == 0) ? 8 : capacity * 2;
      lines = realloc(lines, sizeof(char *) * capacity);
      if (!lines)
        break;
    }
    lines[count] = strdup(line);
    if (!lines[count])
      break;
    if ((int)nread > max_width)
      max_width = (int)nread;
    count++;
  }
  free(line);
  fclose(fp);
  if (!lines || count == 0)
    return false;

  /* Locate player start */
  i = 0;
  while (i < count)
  {
    int j = 0;
    while (lines[i][j])
    {
      if (is_player_char(lines[i][j]))
      {
        player_found = 1;
        map->player_x = j + 0.5;
        map->player_y = i + 0.5;
        map->player_angle = angle_for_char(lines[i][j]);
        lines[i][j] = '0';
      }
      j++;
    }
    i++;
  }
  if (!player_found)
  {
    free_lines(lines, count);
    return false;
  }
  if (!build_layout(map, lines, count, max_width))
  {
    free_lines(lines, count);
    return false;
  }
  free_lines(lines, count);
  map->is_valid = 1;
  return true;
}
