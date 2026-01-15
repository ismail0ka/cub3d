/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:25:57 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 22:02:13 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "cub3d.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

static int	parse_component(const char **cursor)
{
	int			result;
	int			digits;
	const char	*p;

	if (!cursor || ! *cursor)
		return (-1);
	p = *cursor;
	while (ft_isspace(*p))
		p++;
	result = 0;
	digits = 0;
	while (ft_isdigit(*p))
	{
		result = result * 10 + (*p - '0');
		if (result > 255)
			return (-1);
		p++;
		digits++;
	}
	if (digits == 0)
		return (-1);
	*cursor = p;
	return (result);
}

static int	validate_component(int component, char delimiter, char actual)
{
	if (component < 0)
		return (-1);
	if (actual != delimiter)
		return (-1);
	return (0);
}

static int	validate_end(int component, char c)
{
	if (component < 0)
		return (-1);
	if (c != '\0' && !ft_isspace((unsigned char)c))
		return (-1);
	return (0);
}

int	rgb_to_hex(const char *rgb_str)
{
	const char	*p;
	int			r;
	int			g;
	int			b;

	if (!rgb_str)
		return (-1);
	p = rgb_str;
	r = parse_component(&p);
	if (validate_component(r, ',', *p) == -1)
		return (-1);
	p++;
	g = parse_component(&p);
	if (validate_component(g, ',', *p) == -1)
		return (-1);
	p++;
	b = parse_component(&p);
	if (validate_end(b, *p) == -1)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}
