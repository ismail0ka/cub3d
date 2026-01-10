#include "parsing.h"

static char	**copy_and_replace(void);

int	check_map_elements(t_params	*params)
{
	int			i;
	int			j;

	i = -1;
	while (params->map[++i])
	{
		j = -1;
		while (params->map[i][++j])
		{
			if (params->map[i][j] == 'S' || params->map[i][j] == 'N'
				|| params->map[i][j] == 'E' || params->map[i][j] == 'W')
			{
				if (params->player->cell_x != -1 || params->player->cell_y != -1)
					return (ft_putstr_fd("Error: Multiple players in map\n", 2), -1);
				params->player->cell_y = i;
				params->player->cell_x = j;
				params->player->direction = params->map[i][j];
				continue ;
			}
			if (params->map[i][j] != '0' && params->map[i][j] != '1'
				&& params->map[i][j] != ' ' && params->map[i][j] != '\n'
				&& params->map[i][j] != 'N' && params->map[i][j] != 'S'
				&& params->map[i][j] != 'E' && params->map[i][j] != 'W')
				return (-1);
		}
	}
	return (0);
}

static int	check_is_map_open(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if ((map[i][j] == '0' || map[i][j] == 'S'
			|| map[i][j] == 'E' || map[i][j] == 'N'
			|| map[i][j] == 'W')
			&& (i == 0 || j == 0
			|| !map[i + 1] || !map[i][j + 1]
			|| map[i][j + 1] == ' ' || map[i][j - 1] == ' '
			|| map[i + 1][j] == ' ' || map[i - 1][j] == ' '))
				return (-1);
		}
	}
	return (0);
}

int	is_map_surrounded(void)
{
	char		**map;
	t_params	*param;

	param = params_holder();
	map = copy_and_replace();
	if (check_is_map_open(map) == -1)
		return (free_array(&map), -1);
	free_array(&param->map);
	param->map = map;
	return (0);
}

static char	*replace_space(char *str, int longest)
{
	char	*ret;
	int		index;

	index = -1;
	ret = malloc(sizeof(char) * longest + 1);
	if (!ret)
		return (NULL);
	while (str[++index] != '\n' && str[index])
		ret[index] = str[index];
	while (index < longest)
		ret[index++] = ' ';
	ret[index] = '\0';
	return (ret);
}

static char	**copy_and_replace(void)
{
	t_params	*param;
	int			index;
	int			longest;
	char		**ret;

	index = -1;
	longest = 0;
	param = params_holder();
	while (param->map[++index])
	{
		if ((size_t)longest < ft_strlen(param->map[index]))
			longest = ft_strlen(param->map[index]);
	}
	ret = malloc((index + 1) * sizeof(char *));
	if (!ret)
		return (perror("cub3D"), NULL);
	index = -1;
	while (param->map[++index])
		ret[index] = replace_space(param->map[index], longest);
	ret[index] = NULL;
	return (ret);
}