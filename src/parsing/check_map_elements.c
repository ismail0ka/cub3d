/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:27:27 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 17:34:46 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_invalid_char(char c)
{
	return (c != '0' && c != '1' && c != ' ' && c != '\n'
		&& c != 'N' && c != 'S' && c != 'E' && c != 'W');
}

int	check_map_elements(t_params	*p)
{
	int			i;
	int			j;

	i = -1;
	while (p->map[++i])
	{
		j = -1;
		while (p->map[i][++j])
		{
			if (p->map[i][j] == 'S' || p->map[i][j] == 'N'
				|| p->map[i][j] == 'E' || p->map[i][j] == 'W')
			{
				if (p->player->cell_x != -1 || p->player->cell_y != -1)
					return (ft_putstr_fd("Error: Multiple players in map\n", 2)
						, -1);
				p->player->cell_y = i;
				p->player->cell_x = j;
				p->player->direction = p->map[i][j];
				continue ;
			}
			if (is_invalid_char(p->map[i][j]))
				return (-1);
		}
	}
	return (0);
}
