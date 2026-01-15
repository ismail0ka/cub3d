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

static int	split_tex(char *type, char *path)
{
	t_params	*param;
	char		*trimmed_path;

	trimmed_path = trim_texture_path(path);
	if (!trimmed_path || !trimmed_path[0])
		return (ft_putstr_fd("Error: Empty texture path\n", 2), -1);
	if (access(trimmed_path, F_OK) == -1)
		return (ft_putstr_fd("Error: Texture file does not exist\n", 2), -1);
	if (access(trimmed_path, R_OK) == -1)
		return (ft_putstr_fd("Error: Texture file is not readable\n", 2), -1);
	param = params_holder();
	if (type[0] == 'N' && type[1] == 'O')
	{
		if (param->textures[NORTH_TEX])
			return (ft_putstr_fd("Error: Duplicate NO texture\n", 2), -1);
		param->textures[NORTH_TEX] = ft_strdup(trimmed_path);
	}
	else if (type[0] == 'S' && type[1] == 'O')
	{
		if (param->textures[SOUTH_TEX])
			return (ft_putstr_fd("Error: Duplicate SO texture\n", 2), -1);
		param->textures[SOUTH_TEX] = ft_strdup(trimmed_path);
	}
	else if (type[0] == 'W' && type[1] == 'E')
	{
		if (param->textures[WEST_TEX])
			return (ft_putstr_fd("Error: Duplicate WE texture\n", 2), -1);
		param->textures[WEST_TEX] = ft_strdup(trimmed_path);
	}
	else if (type[0] == 'E' && type[1] == 'A')
	{
		if (param->textures[EAST_TEX])
			return (ft_putstr_fd("Error: Duplicate EA texture\n", 2), -1);
		param->textures[EAST_TEX] = ft_strdup(trimmed_path);
	}
	return (0);
}

static int	manage_tex(char ***tmp, t_lines *file_content)
{
	(*tmp) = ft_split(file_content->line, ' ');
	if (!(*tmp) || !(*tmp)[0] || !(*tmp)[1] || (*tmp)[2])
		return (perror("cub3D"), -1);
	if (ft_strlen((*tmp)[0]) != 2)
		return (-1);
	if (split_tex((*tmp)[0], (*tmp)[1]) == -1)
		return (-1);
	return (0);
}

int	add_tex(t_lines *file_content)
{
	char	**tmp;

	tmp = NULL;
	if (!file_content)
		return (-1);
	while (file_content
		&& ((file_content->line[0] == 'N' && file_content->line[1] == 'O')
			|| (file_content->line[0] == 'S' && file_content->line[1] == 'O')
			|| (file_content->line[0] == 'W' && file_content->line[1] == 'E')
			|| (file_content->line[0] == 'E' && file_content->line[1] == 'A')
			|| file_content->line[0] == '\n'))
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
		return (free_array(&tmp), add_color(file_content));
	return (free_array(&tmp), add_map(file_content));
}