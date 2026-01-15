/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:33:22 by yoessedr          #+#    #+#             */
/*   Updated: 2026/01/15 20:08:20 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_row_elements(t_params *params, int i)
{
	int	j;

	j = -1;
	while (params->map[i][++j])
	{
		if (params->map[i][j] == 'S' || params->map[i][j] == 'N'
			|| params->map[i][j] == 'E' || params->map[i][j] == 'W')
		{
			if (params->player->cell_x != -1
				|| params->player->cell_y != -1)
				return (ft_putstr_fd("Error: Multiple players in map\n", 2)
					, -1);
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
	return (0);
}

int	check_map_elements(t_params *params)
{
	int	i;

	i = -1;
	while (params->map[++i])
	{
		if (check_row_elements(params, i) == -1)
			return (-1);
	}
	return (0);
}

int	find_last_char(char *str)
{
	int	last_char;
	int	i;

	last_char = -1;
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != ' ')
			last_char = i;
		i++;
	}
	return (last_char);
}

void	fill_padded_string(char *ret, char *str, int longest, int last_char)
{
	int	index;
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	index = -1;
	while (++index < longest)
	{
		if (index < i)
			ret[index] = str[index];
		else if (index <= last_char)
			ret[index] = '1';
		else
			ret[index] = '?';
	}
	ret[index] = '\0';
}
