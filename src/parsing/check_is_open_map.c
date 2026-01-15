/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_open_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:26:33 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 17:34:33 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_walkable_tile(char c)
{
	if (c == '0' || c == 'S' || c == 'E' || c == 'N' || c == 'W')
		return (1);
	return (0);
}

static int	is_boundary_or_invalid(char **map, int i, int j)
{
	if (i == 0 || j == 0 || ! map[i + 1] || !map[i][j + 1])
		return (1);
	if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
		return (1);
	if (map[i][j + 1] == '?' || map[i][j - 1] == '?')
		return (1);
	if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
		return (1);
	if (map[i + 1][j] == '?' || map[i - 1][j] == '?')
		return (1);
	return (0);
}

static int	check_tile(char **map, int i, int j)
{
	if (!is_walkable_tile(map[i][j]))
		return (0);
	if (is_boundary_or_invalid(map, i, j))
	{
		ft_putstr_fd("Error: Map is not surrounded by walls\n", 2);
		return (-1);
	}
	return (0);
}

int	check_is_map_open(char **map)
{
	int	i;
	int	j;
	int	result;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			result = check_tile(map, i, j);
			if (result == -1)
				return (-1);
		}
	}
	return (0);
}
