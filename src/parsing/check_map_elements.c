/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:27:27 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 23:35:19 by ikarouat         ###   ########.fr       */
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

int	check_map_elements(t_params	*p)
{
	int	i;

	i = -1;
	while (p->map[++i])
	{
		if (check_row_elements(p, i) == -1)
			return (-1);
	}
	return (0);
}
