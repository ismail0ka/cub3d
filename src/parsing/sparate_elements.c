#include "parsing.h"

static int	separate_tex_color(t_lines *file_content)
{
	if ((file_content->line[0] == 'N' && file_content->line[1] == 'O')
		|| (file_content->line[0] == 'S' && file_content->line[1] == 'O')
		|| (file_content->line[0] == 'W' && file_content->line[1] == 'E')
		|| (file_content->line[0] == 'E' && file_content->line[1] == 'A'))
	{
		if (add_tex(file_content) == -1)
			return (-1);
	}
	else if (file_content->line[0] == 'C' || file_content->line[0] == 'F')
	{
		if (add_color(file_content) == -1)
			return (-1);
	}
	return (0);
}

static int	check_elements(void)
{
	t_params	*param;
	int			i;

	i = 0;
	param = params_holder();
	while (i < 3)
	{
		if (param->ceiling_color[i] < 0 || param->ceiling_color[i] > 255
			|| param->floor_color[i] < 0 || param->floor_color[i] > 255)
			return (ft_putstr_fd("Error in colors!!\n", 2), -1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (!param->textures[i] || param->textures[i][0] == '\n')
			return (ft_putstr_fd("Error in textures!!\n", 2), -1);
		i++;
	}
	return (0);
}

int	separate_elements(t_lines *file_content)
{
	t_lines	*tmp;

	tmp = file_content;
	while (tmp && tmp->line[0] == '\n')
		tmp = tmp->next;
	if (separate_tex_color(tmp) == -1)
		return (-1);
	if (check_elements() == -1)
		return (-1);
	return (0);
}