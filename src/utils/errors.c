/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:26:01 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/16 00:41:55 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"

static void	cleanup_textures(t_engine *engine)
{
	int	i;

	if (!engine->renderer || !engine->mlx)
		return ;
	i = 0;
	if (engine->renderer->img)
		mlx_destroy_image(engine->mlx->mlx, engine->renderer->img);
	while (i < NUM_TEXTURES)
	{
		if (engine->renderer->textures[i].img)
			mlx_destroy_image(engine->mlx->mlx,
				engine->renderer->textures[i].img);
		i++;
	}
}

static void	cleanup_mlx(t_engine *engine)
{
	if (! engine->mlx)
		return ;
	if (engine->mlx->win)
		mlx_destroy_window(engine->mlx->mlx, engine->mlx->win);
	if (engine->mlx->mlx)
		mlx_destroy_display(engine->mlx->mlx);
	free(engine->mlx->mlx);
	free(engine->mlx);
}

static void	cleanup_map(t_engine *engine)
{
	if (!engine->map)
		return ;
	free(engine->map->no_texture);
	free(engine->map->so_texture);
	free(engine->map->we_texture);
	free(engine->map->ea_texture);
	free_2d_array(engine->map->layout);
	free(engine->map);
}

void	cleanup_engine(t_engine *engine)
{
	if (!engine)
		return ;
	cleanup_textures(engine);
	cleanup_map(engine);
	cleanup_mlx(engine);
	if (engine->renderer)
		free(engine->renderer);
	if (engine->player)
		free(engine->player);
}

void	exit_with_error(const char *error_message, t_engine *engine)
{
	if (error_message)
		printf("Error: %s\n", error_message);
	cleanup_engine(engine);
	free(engine);
	exit(EXIT_FAILURE);
}
