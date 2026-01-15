/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_elements_textures2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:42:12 by yoessedr          #+#    #+#             */
/*   Updated: 2026/01/15 19:45:34 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	assign_north_south(t_params *param, char *type, char *path)
{
	if (type[0] == 'N' && type[1] == 'O')
	{
		if (param->textures[NORTH_TEX])
			return (ft_putstr_fd("Error: Duplicate NO texture\n", 2), -1);
		param->textures[NORTH_TEX] = ft_strdup(path);
	}
	else if (type[0] == 'S' && type[1] == 'O')
	{
		if (param->textures[SOUTH_TEX])
			return (ft_putstr_fd("Error: Duplicate SO texture\n", 2), -1);
		param->textures[SOUTH_TEX] = ft_strdup(path);
	}
	return (0);
}

static int	assign_west_east(t_params *param, char *type, char *path)
{
	if (type[0] == 'W' && type[1] == 'E')
	{
		if (param->textures[WEST_TEX])
			return (ft_putstr_fd("Error: Duplicate WE texture\n", 2), -1);
		param->textures[WEST_TEX] = ft_strdup(path);
	}
	else if (type[0] == 'E' && type[1] == 'A')
	{
		if (param->textures[EAST_TEX])
			return (ft_putstr_fd("Error: Duplicate EA texture\n", 2), -1);
		param->textures[EAST_TEX] = ft_strdup(path);
	}
	return (0);
}

static int	is_valid_xpm(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (path[len - 1] != 'm' || path[len - 2] != 'p'
		|| path[len - 3] != 'x' || path[len - 4] != '.')
		return (0);
	return (1);
}

int	split_tex(char *type, char *path)
{
	t_params	*param;
	char		*trimmed_path;

	trimmed_path = trim_texture_path(path);
	if (!trimmed_path || !trimmed_path[0])
		return (ft_putstr_fd("Error: Empty texture path\n", 2), -1);
	if (!is_valid_xpm(trimmed_path))
		return (ft_putstr_fd("Error: Texture must be .xpm file\n", 2), -1);
	if (access(trimmed_path, F_OK) == -1)
		return (ft_putstr_fd("Error: Texture file does not exist\n", 2), -1);
	if (access(trimmed_path, R_OK) == -1)
		return (ft_putstr_fd("Error: Texture file is not readable\n", 2), -1);
	param = params_holder();
	if (assign_north_south(param, type, trimmed_path) == -1)
		return (-1);
	if (assign_west_east(param, type, trimmed_path) == -1)
		return (-1);
	return (0);
}
