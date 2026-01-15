/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:15:14 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/14 23:31:02 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	angle_for_char(char c)
{
	if (c == 'N')
		return (-M_PI_2);
	if (c == 'S')
		return (M_PI_2);
	if (c == 'E')
		return (0.0);
	return (M_PI);
}

static void	copy_map_row(char **dst, char **src, int i, int w)
{
	int	j;

	j = 0;
	while (j < w && src[i][j])
	{
		dst[i][j] = src[i][j];
		j++;
	}
	while (j < w)
	{
		dst[i][j] = '1';
		j++;
	}
	dst[i][w] = '\0';
}

char	**alloc_map_lines(char **src, int h, int w)
{
	char	**dst;
	int		i;

	dst = calloc(h + 1, sizeof(char *));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < h)
	{
		dst[i] = malloc((size_t)w + 1);
		if (!dst[i])
			return (NULL);
		copy_map_row(dst, src, i, w);
		i++;
	}
	dst[h] = NULL;
	return (dst);
}

char	**dup_map_lines(char **src, int *out_h, int *out_w)
{
	int		h;
	int		w;
	char	**dst;

	if (!src)
		return (NULL);
	h = 0;
	while (src[h])
		h++;
	w = 0;
	if (src[0])
		w = (int)ft_strlen(src[0]);
	dst = alloc_map_lines(src, h, w);
	if (out_h)
		*out_h = h;
	if (out_w)
		*out_w = w;
	return (dst);
}
