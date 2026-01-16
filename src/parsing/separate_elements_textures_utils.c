/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_elements_textures_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:39:50 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/16 01:04:31 by ikarouat         ###   ########.fr       */
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

static int	validate_texture_path(char *path)
{
	if (!path || !path[0])
	{
		ft_putstr_fd("Error: Empty texture path\n", 2);
		return (-1);
	}
	if (!is_valid_xpm(path))
		return (ft_putstr_fd("Error: Texture must be .xpm file\n", 2), -1);
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
