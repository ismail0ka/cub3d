/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:28 by yoessedr          #+#    #+#             */
/*   Updated: 2026/01/11 20:43:28 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		;
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
	free(*params);
}
