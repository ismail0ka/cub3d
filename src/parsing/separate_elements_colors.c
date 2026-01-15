/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_elements_colors.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:36 by yoessedr          #+#    #+#             */
/*   Updated: 2026/01/11 20:43:36 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	process_color_line(t_lines *file_content)
{
	char		*color_type;
	char		*color_str;
	char		*ptr;

	if (file_content->line[1] != ' ' && file_content->line[1] != '\t')
		return (ft_putstr_fd("Error: Invalid color identifier\n", 2), -1);
	color_type = ft_substr(file_content->line, 0, 1);
	if (!color_type)
		return (perror("cub3D"), -1);
	ptr = file_content->line;
	while (*ptr && *ptr != ' ' && *ptr != '\t')
		ptr++;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	color_str = ft_strdup(ptr);
	if (!color_str)
		return (free(color_type), perror("cub3D"), -1);
	if (split_color(color_type, color_str) == -1)
		return (free(color_type), free(color_str), -1);
	free(color_type);
	free(color_str);
	return (0);
}

int	add_color(t_lines *file_content)
{
	if (!file_content)
		return (-1);
	while (file_content && (file_content->line[0] == 'F'
			|| file_content->line[0] == 'C' || file_content->line[0] == '\n'))
	{
		if (file_content->line[0] == 'F' || file_content->line[0] == 'C')
		{
			if (process_color_line(file_content) == -1)
				return (-1);
		}
		file_content = file_content->next;
	}
	if (!params_holder()->textures[NORTH_TEX])
		return (add_tex(file_content));
	return (add_map(file_content));
}
