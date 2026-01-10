#include "parsing.h"

static int	split_map(t_lines *file_content, size_t len)
{
	t_params	*param;
	size_t		index;

	index = 0;
	param = params_holder();
	param->map = malloc(sizeof(char *) * (len + 1));
	if (!param->map)
		return (perror("cub3D"), -1);
	while (index < len)
	{
		param->map[index] = ft_strdup(file_content->line);
		index++;
		file_content = file_content->next;
	}
	param->map[index] = NULL;
	return (0);
}

int	add_map(t_lines *file_content_i)
{
	size_t	len;
	t_lines	*file_content;

	len = 0;
	file_content = file_content_i;
	if (!file_content)
		return (-1);
	while (file_content && file_content->line && ((file_content->line[0] == '0'
				|| file_content->line[0] == '1' || file_content->line[0] == ' '
				|| file_content->line[0] == '\n' || file_content->line[0] == 'N'
				|| file_content->line[0] == 'S' || file_content->line[0] == 'E'
				|| file_content->line[0] == 'W')))
	{
		if (file_content->line[0] != '\n')
			len++;
		else
		{
			while (file_content && file_content->line)
			{
				if (file_content->line[0] != '\n')
					return (-1);
				file_content = file_content->next;
			}
			if (!file_content || !file_content->line)
				break;
		}
		file_content = file_content->next;
	}
	return (split_map(file_content_i, len));
}