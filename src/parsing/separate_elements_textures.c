/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_elements_textures.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:41 by yoessedr          #+#    #+#             */
/*   Updated: 2026/01/11 20:43:41 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_valid_direction(char *s)
{
	return ((s[0] == 'N' && s[1] == 'O') || (s[0] == 'S' && s[1] == 'O')
		|| (s[0] == 'W' && s[1] == 'E') || (s[0] == 'E' && s[1] == 'A')
		|| s[0] == '\n');
}

int	add_tex(t_lines *file_content)
{
	char	**tmp;

	tmp = NULL;
	if (!file_content)
		return (-1);
	while (file_content && is_valid_direction(file_content->line))
	{
		if (file_content->line[0] != '\n')
		{
			if (manage_tex(&tmp, file_content) == -1)
				return (free_array(&tmp), -1);
			free_array(&tmp);
		}
		file_content = file_content->next;
	}
	if (params_holder()->floor_color[0] == -1)
	{
		free_array(&tmp);
		return (add_color(file_content));
	}
	free_array(&tmp);
	return (add_map(file_content));
}

int	assign_texture(t_params *param, char *type, char *path)
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
