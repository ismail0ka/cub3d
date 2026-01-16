/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_open_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:26:33 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/16 01:02:03 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_space_adjacent(char **map, int i, int j)
{
	if ((j > 0 && (map[i][j - 1] == '0' || map[i][j - 1] == 'S'
		|| map[i][j - 1] == 'E' || map[i][j - 1] == 'N'
		|| map[i][j - 1] == 'W'))
		|| (map[i][j + 1] && (map[i][j + 1] == '0'
			|| map[i][j + 1] == 'S' || map[i][j + 1] == 'E'
			|| map[i][j + 1] == 'N' || map[i][j + 1] == 'W'))
		|| (i > 0 && (map[i - 1][j] == '0' || map[i - 1][j] == 'S'
			|| map[i - 1][j] == 'E' || map[i - 1][j] == 'N'
			|| map[i - 1][j] == 'W'))
		|| (map[i + 1] && (map[i + 1][j] == '0'
			|| map[i + 1][j] == 'S' || map[i + 1][j] == 'E'
			|| map[i + 1][j] == 'N' || map[i + 1][j] == 'W')))
		return (1);
	return (0);
}

int	check_is_map_open(char **map)
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
			&& (!map[i + 1] || !map[i][j + 1]
			|| map[i][j + 1] == '?' || map[i][j - 1] == '?'
			|| map[i + 1][j] == '?' || (i > 0 && map[i - 1][j] == '?')))
				return (ft_putstr_fd("Error: Map is not surrounded by walls\n"
						, 2), -1);
			if (map[i][j] == ' ' && check_space_adjacent(map, i, j))
				return (ft_putstr_fd("Error: Map is not surrounded by walls\n"
						, 2), -1);
		}
	}
	return (0);
}
