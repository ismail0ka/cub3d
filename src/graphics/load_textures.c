/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:25:33 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/14 23:37:19 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "cub3d.h"

static void	load_texture(t_mlx *mlx, t_texture *texture, char *path)
{
	if (!path || !mlx || !texture)
		return ;
	texture->img = mlx_xpm_file_to_image(mlx->mlx, path,
			&texture->width, &texture->height);
	if (texture->img)
		texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
				&texture->line_len, &texture->endian);
}

void	init_renderer(t_renderer *renderer, t_mlx *mlx, t_map *map)
{
	int	i;

	if (!renderer || !mlx || !map)
		return ;
	i = 0;
	while (i < NUM_TEXTURES)
	{
		ft_memset(&renderer->textures[i], 0, sizeof(renderer->textures[i]));
		i++;
	}
	load_texture(mlx, &renderer->textures[0], map->no_texture);
	load_texture(mlx, &renderer->textures[1], map->so_texture);
	load_texture(mlx, &renderer->textures[2], map->we_texture);
	load_texture(mlx, &renderer->textures[3], map->ea_texture);
	i = 0;
	while (i < WIN_WIDTH)
	{
		renderer->z_buffer[i] = 0.0;
		i++;
	}
	renderer->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	if (renderer->img)
		renderer->addr = mlx_get_data_addr(renderer->img, &renderer->bpp,
				&renderer->line_len, &renderer->endian);
}
