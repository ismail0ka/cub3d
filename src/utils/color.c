#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "cub3d.h"

static int  parse_component(const char **cursor)
{
	char    *end;
	long     value;

	if (!cursor || !*cursor)
		return -1;
	value = strtol(*cursor, &end, 10);
	if (end == *cursor || value < 0 || value > 255)
		return -1;
	*cursor = end;
	return (int)value;
}

int rgb_to_hex(const char *rgb_str)
{
	const char  *p;
	int          r;
	int          g;
	int          b;

	if (!rgb_str)
		return -1;
	p = rgb_str;
	r = parse_component(&p);
	if (r < 0 || *p != ',')
		return -1;
	p++;
	g = parse_component(&p);
	if (g < 0 || *p != ',')
		return -1;
	p++;
	b = parse_component(&p);
	if (b < 0 || (*p != '\0' && !isspace((unsigned char)*p)))
		return -1;
	return (r << 16) | (g << 8) | b;
}

void  free_2d_array(char **arr)
{
	size_t i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
