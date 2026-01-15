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

char	*trim_texture_path(char *path)
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

static int	manage_tex(char ***tmp, t_lines *file_content)
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

static int	process_texture_lines(char ***tmp, t_lines **file_content)
{
	while (*file_content
		&& (((*file_content)->line[0] == 'N' && (*file_content)->line[1] == 'O')
			|| ((*file_content)->line[0] == 'S'
				&& (*file_content)->line[1] == 'O')
			|| ((*file_content)->line[0] == 'W'
				&& (*file_content)->line[1] == 'E')
			|| ((*file_content)->line[0] == 'E'
				&& (*file_content)->line[1] == 'A')
			|| (*file_content)->line[0] == '\n'))
	{
		if ((*file_content)->line[0] != '\n')
		{
			if (manage_tex(tmp, *file_content) == -1)
				return (-1);
			free_array(tmp);
		}
		*file_content = (*file_content)->next;
	}
	return (0);
}

int	add_tex(t_lines *file_content)
{
	char	**tmp;

	tmp = NULL;
	if (!file_content)
		return (-1);
	if (process_texture_lines(&tmp, &file_content) == -1)
		return (free_array(&tmp), -1);
	if (params_holder()->floor_color[0] == -1)
	{
		free_array(&tmp);
		return (add_color(file_content));
	}
	free_array(&tmp);
	return (add_map(file_content));
}
