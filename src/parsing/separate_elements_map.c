/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_elements_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:38 by yoessedr          #+#    #+#             */
/*   Updated: 2026/01/11 20:43:38 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	split_map(t_lines *file_content, size_t len)
{
	t_params	*param;
	size_t		index;

	index = 0;
	param = params_holder();
	param->map = malloc(sizeof(char *) * (len + 1));
	if (!param->map)
		return (perror("cub3D"), -1);
	while (index < len)
	{
		param->map[index] = ft_strdup(file_content->line);
		index++;
		file_content = file_content->next;
	}
	param->map[index] = NULL;
	return (0);
}

static int	is_map_char(char c)
{
	if (c == '0' || c == '1' || c == '\n'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	validate_trailing_lines(t_lines *file_content)
{
	while (file_content && file_content->line)
	{
		if (file_content->line[0] != '\n')
			return (-1);
		file_content = file_content->next;
	}
	return (0);
}

int	chcker(char *str)
{
	int i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] &&  str[i] != '\n')
	{
		if (str[i] != ' ' && str[i] != '\t')
		return (0);
		i++;
	}
	return (1);
}

static int	count_map_lines(t_lines *file_content, size_t *len)
{
	while (file_content && file_content->line
		&& is_map_char(file_content->line[0]))
	{
		if (!chcker(file_content->line))
			(*len)++;
		else
		{
			if (validate_trailing_lines(file_content) == -1)
				return (-1);
			break ;
		}
		file_content = file_content->next;
	}
	return (0);
}

int	add_map(t_lines *file_content_i)
{
	size_t	len;

	len = 0;
	if (!file_content_i)
		return (-1);
	if (count_map_lines(file_content_i, &len) == -1)
		return (-1);
	return (split_map(file_content_i, len));
}
