/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:13 by yoessedr          #+#    #+#             */
/*   Updated: 2026/01/11 20:43:13 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**copy_and_replace(void);

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
			|| map[i][j + 1] == '?' || map[i][j - 1] == '?'
			|| map[i + 1][j] == '?' || map[i - 1][j] == '?'))
				return (ft_putstr_fd("Error: Map is not surrounded by walls\n"
						, 2), -1);
		}
	}
	return (0);
}
int	is_map_surrounded(void)
{
	char		**map;
	t_params	*param;
	int			result;

	param = params_holder();
	map = copy_and_replace();
	if (!map)
		return (-1);
	result = check_is_map_open(map);
	free_array(&map);
	if (result == -1)
		return (-1);
	return (0);
}

static char	*replace_space(char *str, int longest)
{
	char	*ret;
	int		last_char;

	ret = malloc(sizeof(char) * longest + 1);
	if (!ret)
		return (NULL);
	last_char = find_last_char(str);
	fill_padded_string(ret, str, longest, last_char);
	return (ret);
}

static char	**copy_and_replace(void)
{
	t_params	*param;
	int			index;
	int			longest;
	char		**ret;
	int			len;

	index = -1;
	longest = 0;
	param = params_holder();
	while (param->map[++index])
	{
		len = ft_strlen(param->map[index]);
		if (param->map[index][len - 1] == '\n')
			len--;
		if (longest < len)
			longest = len;
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
