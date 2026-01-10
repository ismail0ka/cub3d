#include "parsing.h"

static char	*skip_whitespace(char *str)
{
	while (str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

static char	*trim_whitespace(char *str)
{
	int	len;

	if (!str)
		return (str);
	str = skip_whitespace(str);
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
			|| str[len - 1] == '\n'))
	{
		str[len - 1] = '\0';
		len--;
	}
	return (str);
}

static int	is_color_digit(char *color)
{
	int		i;
	char	*trimmed;

	trimmed = trim_whitespace(color);
	if (!trimmed || !trimmed[0])
		return (-1);
	i = -1;
	while (trimmed[++i])
	{
		if (!ft_isdigit(trimmed[i]) && trimmed[i] != '\n')
			return (-1);
	}
	return (0);
}

static int	split_color(char *type, char *colors)
{
	char		**tmp;
	t_params	*param;

	param = params_holder();
	tmp = ft_split(colors, ',');
	if (!tmp)
		return (perror("cub3D"), -1);
	if (!tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
		return (ft_putstr_fd("!!Error in colors!!\n", 2), free_array(&tmp), -1);
#ifdef DEBUG_COLOR
	ft_putstr_fd("DEBUG tokens -> ", 2);
	if (tmp[0]) ft_putstr_fd(tmp[0], 2);
	ft_putstr_fd(" | ", 2);
	if (tmp[1]) ft_putstr_fd(tmp[1], 2);
	ft_putstr_fd(" | ", 2);
	if (tmp[2]) ft_putstr_fd(tmp[2], 2);
	ft_putstr_fd("\n", 2);
#endif
	/* Validate each color component is a digit after trimming */
	if (is_color_digit(tmp[0]) == -1 || is_color_digit(tmp[1]) == -1
		|| is_color_digit(tmp[2]) == -1)
		return (ft_putstr_fd("!!Error in colors!!\n", 2), free_array(&tmp), -1);
	if (type[0] == 'F')
	{
		if (param->floor_color[0] != -1)
			return (ft_putstr_fd("Error: Duplicate F color\n", 2), free_array(&tmp), -1);
		param->floor_color[0] = ft_atoi(trim_whitespace(tmp[0]));
		param->floor_color[1] = ft_atoi(trim_whitespace(tmp[1]));
		param->floor_color[2] = ft_atoi(trim_whitespace(tmp[2]));
	}
	else if (type[0] == 'C')
	{
		if (param->ceiling_color[0] != -1)
			return (ft_putstr_fd("Error: Duplicate C color\n", 2), free_array(&tmp), -1);
		param->ceiling_color[0] = ft_atoi(trim_whitespace(tmp[0]));
		param->ceiling_color[1] = ft_atoi(trim_whitespace(tmp[1]));
		param->ceiling_color[2] = ft_atoi(trim_whitespace(tmp[2]));
	}
	return (free_array(&tmp), 0);
}

int	add_color(t_lines *file_content)
{
	char		*color_type;
	char		*color_str;
	char		*ptr;

	if (!file_content)
		return (-1);
	while (file_content && (file_content->line[0] == 'F'
			|| file_content->line[0] == 'C' || file_content->line[0] == '\n'))
	{
		if (file_content->line[0] == 'F' || file_content->line[0] == 'C')
		{
			color_type = ft_substr(file_content->line, 0, 1);
			if (!color_type)
				return (perror("cub3D"), -1);
			/* Find first whitespace (space or tab) then skip any whitespace to get colors */
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
		}
		file_content = file_content->next;
	}
	if (!params_holder()->textures[NORTH_TEX])
		return (add_tex(file_content));
	return (add_map(file_content));
}