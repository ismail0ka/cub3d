/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_elements_colors_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:47:59 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 17:58:47 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*trim_whitespace(char *str)
{
	int	len;

	if (!str)
		return (str);
	while (str && (*str == ' ' || *str == '\t'))
		str++;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
			|| str[len - 1] == '\n'))
	{
		str[len - 1] = '\0';
		len--;
	}
	return (str);
}

static int	count_commas(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static int	is_color_digit(char *color)
{
	int		i;
	char	*trimmed;

	trimmed = trim_whitespace(color);
	if (!trimmed || !trimmed[0])
		return (-1);
	i = -1;
	while (trimmed[++i])
	{
		if (!ft_isdigit(trimmed[i]) && trimmed[i] != '\n')
			return (-1);
	}
	return (0);
}

static int	assign_color_values(t_params *param, char *type, char **tmp)
{
	if (type[0] == 'F')
	{
		if (param->floor_color[0] != -1)
		{
			ft_putstr_fd("Error: Duplicate F color\n", 2);
			return (free_array(&tmp), -1);
		}
		param->floor_color[0] = ft_atoi(trim_whitespace(tmp[0]));
		param->floor_color[1] = ft_atoi(trim_whitespace(tmp[1]));
		param->floor_color[2] = ft_atoi(trim_whitespace(tmp[2]));
	}
	else if (type[0] == 'C')
	{
		if (param->ceiling_color[0] != -1)
		{
			ft_putstr_fd("Error: Duplicate C color\n", 2);
			return (free_array(&tmp), -1);
		}
		param->ceiling_color[0] = ft_atoi(trim_whitespace(tmp[0]));
		param->ceiling_color[1] = ft_atoi(trim_whitespace(tmp[1]));
		param->ceiling_color[2] = ft_atoi(trim_whitespace(tmp[2]));
	}
	return (0);
}

int	split_color(char *type, char *colors)
{
	char		**tmp;
	t_params	*param;
	int			result;

	param = params_holder();
	if (count_commas(colors) != 2)
		return (ft_putstr_fd("!!Error in colors! !\n", 2), -1);
	tmp = ft_split(colors, ',');
	if (!tmp)
		return (perror("cub3D"), -1);
	if (!tmp[0] || !tmp[1] || !tmp[2] || tmp[3])
		return (ft_putstr_fd("!!Error in colors!!\n", 2),
			free_array(&tmp), -1);
	if (is_color_digit(tmp[0]) == -1 || is_color_digit(tmp[1]) == -1
		|| is_color_digit(tmp[2]) == -1)
		return (ft_putstr_fd("!! Error in colors!!\n", 2),
			free_array(&tmp), -1);
	result = assign_color_values(param, type, tmp);
	if (result == -1)
		return (-1);
	return (free_array(&tmp), 0);
}
