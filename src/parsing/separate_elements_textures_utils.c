/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_elements_textures_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:39:50 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 17:46:51 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*trim_texture_path(char *path)
{
	char	*start;
	char	*end;

	start = path;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	if (!*start)
		return (NULL);
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
	{
		*end = '\0';
		end--;
	}
	return (start);
}

static int	validate_texture_path(char *path)
{
	if (!path || !path[0])
	{
		ft_putstr_fd("Error: Empty texture path\n", 2);
		return (-1);
	}
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("Error: Texture file does not exist\n", 2);
		return (-1);
	}
	if (access(path, R_OK) == -1)
	{
		ft_putstr_fd("Error:  Texture file is not readable\n", 2);
		return (-1);
	}
	return (0);
}

static int	assign_texture(t_params *param, char *type, char *path)
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
			return (ft_putstr_fd("Error:  Duplicate SO texture\n", 2), -1);
		param->textures[SOUTH_TEX] = ft_strdup(path);
	}
	else if (type[0] == 'W' && type[1] == 'E')
	{
		if (param->textures[WEST_TEX])
			return (ft_putstr_fd("Error: Duplicate WE texture\n", 2), -1);
		param->textures[WEST_TEX] = ft_strdup(path);
	}
	else if (type[0] == 'E' && type[1] == 'A')
	{
		if (param->textures[EAST_TEX])
			return (ft_putstr_fd("Error:  Duplicate EA texture\n", 2), -1);
		param->textures[EAST_TEX] = ft_strdup(path);
	}
	return (0);
}

static int	split_tex(char *type, char *path)
{
	t_params	*param;
	char		*trimmed_path;

	trimmed_path = trim_texture_path(path);
	if (validate_texture_path(trimmed_path) == -1)
		return (-1);
	param = params_holder();
	return (assign_texture(param, type, trimmed_path));
}

int	manage_tex(char ***tmp, t_lines *file_content)
{
	(*tmp) = ft_split(file_content->line, ' ');
	if (!(*tmp) || !(*tmp)[0] || !(*tmp)[1] || (*tmp)[2])
		return (perror("cub3D"), -1);
	if (ft_strlen((*tmp)[0]) != 2)
		return (ft_putstr_fd("Error: Invalid texture identifier\n",
				2), -1);
	if (((*tmp)[0][0] != 'N' || (*tmp)[0][1] != 'O')
		&& ((*tmp)[0][0] != 'S' || (*tmp)[0][1] != 'O')
		&& ((*tmp)[0][0] != 'W' || (*tmp)[0][1] != 'E')
		&& ((*tmp)[0][0] != 'E' || (*tmp)[0][1] != 'A'))
		return (ft_putstr_fd("Error: Invalid texture identifier\n",
				2), -1);
	if (split_tex((*tmp)[0], (*tmp)[1]) == -1)
		return (-1);
	return (0);
}
