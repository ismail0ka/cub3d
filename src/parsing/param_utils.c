#include "parsing.h"

t_params	*params_holder(void)
{
	static t_params	*ret;

	if (ret == NULL)
		ret = malloc(sizeof(t_params));
	return (ret);
}

void	separate_init(t_params **params, t_raydata *ray, t_playerdata *player)
{
	(*params)->player = player;
	(*params)->mlx = NULL;
	(*params)->player->pixel_y = -1;
	(*params)->player->pixel_x = -1;
	(*params)->player->cell_y = -1;
	(*params)->player->cell_x = -1;
	(*params)->player->direction = 0;
	(*params)->ray = ray;
	(*params)->ray->distance_per_y = 0;
	(*params)->ray->distance_per_x = 0;
	(*params)->ray->dir_y = 0;
	(*params)->ray->dir_x = 0;
	(*params)->ray->ray_length = 0;
	(*params)->player_move = 0;
}

void	params_init(t_params **params, t_raydata *ray, t_playerdata *player)
{
	int	index;

	index = -1;
	(*params)->map = NULL;
	while (++index < ALL_TEXTURES)
		(*params)->textures[index] = NULL;
	index = -1;
	while (++index < 3)
	{
		(*params)->ceiling_color[index] = -1;
		(*params)->floor_color[index] = -1;
	}
	index = -1;
	while (++index < 4)
	{
		(*params)->tex_info[index].img = NULL;
		(*params)->tex_info[index].addr = NULL;
	}
	separate_init(params, ray, player);
}

void	free_params(t_params **params)
{
	int	index;

	index = 0;
	while (index < ALL_TEXTURES)
		free ((*params)->textures[index++]);
	index = -1;
	if ((*params)->map)
		free_array(&(*params)->map);
	if ((*params)->mlx)
	{
		/*
		while (++index < 4 && (*params)->tex_info[index].img)
			mlx_destroy_image((*params)->mlx->mlx_ptr,
				(*params)->tex_info[index].img);
		mlx_destroy_image((*params)->mlx->mlx_ptr, (*params)->img->img_ptr);
		mlx_destroy_window((*params)->mlx->mlx_ptr, (*params)->mlx->win_ptr);
		mlx_destroy_display((*params)->mlx->mlx_ptr);
		free((*params)->mlx->mlx_ptr);
		*/
	}
	free (*params);
}