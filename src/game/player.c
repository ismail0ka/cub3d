#include "cub3d.h"

void init_player(t_player *player, const t_map *map)
{
    double angle;

    if (!player || !map)
        return;
    angle = map->player_angle;
    player->pos.x = map->player_x;
    player->pos.y = map->player_y;
    player->direction.x = cos(angle);
    player->direction.y = sin(angle);
    player->plane.x = -player->direction.y * 0.66;
    player->plane.y = player->direction.x * 0.66;
    player->move_speed = 0.1;
    player->rot_speed = 0.05;
}

void move_forward(t_player *player, char **map) {
    double new_x = player->pos.x + player->direction.x * player->move_speed;
    double new_y = player->pos.y + player->direction.y * player->move_speed;
    int    mx;
    int    my;

    mx = (int)new_x;
    my = (int)new_y;
    if (my >= 0 && map[my] && map[my][(int)player->pos.x] != '1')
        player->pos.y = new_y;
    mx = (int)new_x;
    my = (int)player->pos.y;
    if (my >= 0 && map[my] && map[my][mx] != '1')
        player->pos.x = new_x;
}

void move_backward(t_player *player, char **layout) {
    double next_x = player->pos.x - player->direction.x * player->move_speed;
    double next_y = player->pos.y - player->direction.y * player->move_speed;
    int    mx;
    int    my;

    my = (int)next_y;
    if (my >= 0 && layout[my] && layout[my][(int)player->pos.x] != '1')
        player->pos.y = next_y;
    mx = (int)next_x;
    my = (int)player->pos.y;
    if (my >= 0 && layout[my] && layout[my][mx] != '1')
        player->pos.x = next_x;
}

void strafe_left(t_player *player, char **layout) {
    double next_x = player->pos.x - player->plane.x * player->move_speed;
    double next_y = player->pos.y - player->plane.y * player->move_speed;
    int    mx;
    int    my;

    my = (int)next_y;
    if (my >= 0 && layout[my] && layout[my][(int)player->pos.x] != '1')
        player->pos.y = next_y;
    mx = (int)next_x;
    my = (int)player->pos.y;
    if (my >= 0 && layout[my] && layout[my][mx] != '1')
        player->pos.x = next_x;
}

void strafe_right(t_player *player, char **layout) {
    double next_x = player->pos.x + player->plane.x * player->move_speed;
    double next_y = player->pos.y + player->plane.y * player->move_speed;
    int    mx;
    int    my;

    my = (int)next_y;
    if (my >= 0 && layout[my] && layout[my][(int)player->pos.x] != '1')
        player->pos.y = next_y;
    mx = (int)next_x;
    my = (int)player->pos.y;
    if (my >= 0 && layout[my] && layout[my][mx] != '1')
        player->pos.x = next_x;
}

void rotate_right(t_player *player) {
    double old_dir_x = player->direction.x;
    player->direction.x = cos(-player->rot_speed) * old_dir_x - sin(-player->rot_speed) * player->direction.y;
    player->direction.y = sin(-player->rot_speed) * old_dir_x + cos(-player->rot_speed) * player->direction.y;
    // Rotate the camera plane too
    double old_plane_x = player->plane.x;
    player->plane.x = cos(-player->rot_speed) * old_plane_x - sin(-player->rot_speed) * player->plane.y;
    player->plane.y = sin(-player->rot_speed) * old_plane_x + cos(-player->rot_speed) * player->plane.y;
}

void rotate_left(t_player *player) {
    double old_dir_x = player->direction.x;
    player->direction.x = player->direction.x * cos(player->rot_speed)
                        - player->direction.y * sin(player->rot_speed);
    player->direction.y = old_dir_x * sin(player->rot_speed)
                        + player->direction.y * cos(player->rot_speed);

    double old_plane_x = player->plane.x;
    player->plane.x = player->plane.x * cos(player->rot_speed)
                    - player->plane.y * sin(player->rot_speed);
    player->plane.y = old_plane_x * sin(player->rot_speed)
                    + player->plane.y * cos(player->rot_speed);
}
